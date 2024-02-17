#pragma once
#include "Script.hpp"
#include "Natives.hpp"

namespace Saint
{
	class AbstractCallback
	{
	public:
		virtual ~AbstractCallback() noexcept = default;
		AbstractCallback(AbstractCallback const&) = delete;
		AbstractCallback& operator=(AbstractCallback const&) = delete;
		AbstractCallback(AbstractCallback&&) = delete;
		AbstractCallback& operator=(AbstractCallback&&) = delete;

		/**
		 * \brief Is the callback completed?
		 * \return bool
		 */
		virtual bool IsDone() = 0;

		/**
		 * \brief Called when IsDone() returns true
		 */
		virtual void OnSuccess() = 0;

		/**
		 * \brief Called when IsDone() returns false 
		 */
		virtual void OnFailure() = 0;
	protected:
		AbstractCallback() = default;
	};
	class WeaponModelCallback : public AbstractCallback
	{
	public:
		explicit WeaponModelCallback(std::uint32_t model, std::function<void()> action) :
			m_Model(model),
			m_Action(std::move(action))
		{
		}

		bool IsDone() override
		{
			return WEAPON::HAS_WEAPON_ASSET_LOADED(m_Model);
		}

		void OnSuccess() override
		{
			if (m_Action)
				std::invoke(m_Action);
		}

		void OnFailure() override
		{
			WEAPON::REQUEST_WEAPON_ASSET(m_Model, 31, 0);
		}
	private:
		std::uint32_t m_Model;
		std::function<void()> m_Action;
	};
	class PTFXCallback : public AbstractCallback
	{
	public:
		explicit PTFXCallback(const char* particleName, std::function<void()> action) :
			m_ParticleName(particleName),
			m_Action(std::move(action))
		{
		}

		bool IsDone() override
		{
			return STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(m_ParticleName);
		}

		void OnSuccess() override
		{
			if (m_Action)
				std::invoke(m_Action);
		}

		void OnFailure() override
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET(m_ParticleName);
		}
	private:
		const char* m_ParticleName;
		std::function<void()> m_Action;
	};
	class WalkStyleCallback : public AbstractCallback
	{
	public:
		explicit WalkStyleCallback(const char* walkStyle, std::function<void()> action) :
			m_WalkStyle(walkStyle),
			m_Action(std::move(action))
		{
		}

		bool IsDone() override
		{
			return STREAMING::HAS_ANIM_SET_LOADED(m_WalkStyle);
		}

		void OnSuccess() override
		{
			if (m_Action)
				std::invoke(m_Action);
		}

		void OnFailure() override
		{
			STREAMING::REQUEST_ANIM_SET(m_WalkStyle);
		}
	private:
		const char* m_WalkStyle;
		std::function<void()> m_Action;
	};
	class AnimationCallback : public AbstractCallback
	{
	public:
		explicit AnimationCallback(const char* anim, std::function<void()> action) :
			m_Name(anim),
			m_Action(std::move(action))
		{
		}

		bool IsDone() override
		{
			return STREAMING::HAS_ANIM_DICT_LOADED(m_Name);
		}

		void OnSuccess() override
		{
			if (m_Action)
				std::invoke(m_Action);
		}

		void OnFailure() override
		{
			STREAMING::REQUEST_ANIM_DICT(m_Name);
		}
	private:
		const char* m_Name;
		std::function<void()> m_Action;
	};
	class ModelCallback : public AbstractCallback
	{
	public:
		explicit ModelCallback(std::uint32_t model, std::function<void()> action):
			m_Model(model),
			m_Action(std::move(action))
		{
		}

		bool IsDone() override
		{
			return STREAMING::HAS_MODEL_LOADED(m_Model);
		}

		void OnSuccess() override
		{
			if (m_Action)
				std::invoke(m_Action);
		}

		void OnFailure() override
		{
			STREAMING::REQUEST_MODEL(m_Model);
		}
	private:
		std::uint32_t m_Model;
		std::function<void()> m_Action;
	};
	class KeyboardCallBack : public AbstractCallback
	{
	public:
		explicit KeyboardCallBack(const char* title, int input, std::function<void()> action) :
			Title(Title),
			m_Action(std::move(action)),
			Input(input)
		{
		}

		bool IsDone() override
		{
			int update = MISC::UPDATE_ONSCREEN_KEYBOARD();
			switch (update) {
			case -1:
				return false;
				break;
			case 0:
				return false;
				break;
			case 1:
				if (MISC::GET_ONSCREEN_KEYBOARD_RESULT() != Title) {
					return true;
				}
				break;
			case 2:
				return true;
				break;
			}
			return false;

		}

		void OnSuccess() override
		{
			if (m_Action)
				std::invoke(m_Action);
		}

		void OnFailure() override
		{

		}
	private:
		const char* Title;
		int Input;
		std::function<void()> m_Action;
	};
	class NetworkControlCallback : public AbstractCallback
	{
	public:
		explicit NetworkControlCallback(std::int32_t entity, std::function<void()> action):
			m_Entity(entity),
			m_Action(std::move(action))
		{
		}

		bool IsDone() override
		{
			return NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(m_Entity);
		}

		void OnSuccess() override
		{
			if (m_Action)
				std::invoke(m_Action);
		}

		void OnFailure() override
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(m_Entity);
		}
	private:
		std::int32_t m_Entity;
		std::function<void()> m_Action;
	};

	class CallbackScript : public Script
	{
	public:
		explicit CallbackScript() = default;
		~CallbackScript() noexcept = default;

		bool IsInitialized() override;
		ScriptType GetType() override;
		void Initialize() override;
		void Destroy() override;
		void Tick() override;

		/**
		 * \brief Adds a callback to the list
		 * \param args... The arguments to be passed to CallbackType's constructor
		 */
		template <typename CallbackType, typename ...TArgs>
		void AddCallback(TArgs&&... args)
		{
			m_Callbacks.push_back(std::make_unique<CallbackType>(std::forward<TArgs>(args)...));
		}
	private:
		bool m_Initialized{};
		std::vector<std::unique_ptr<AbstractCallback>> m_Callbacks;
	};

	inline std::shared_ptr<CallbackScript> g_CallbackScript;
}
