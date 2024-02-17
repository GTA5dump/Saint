#pragma once
#include "Common.hpp"
#include "Logger.hpp"
#include <map>

namespace Saint {
	
	class fbr {
	public:
		fbr(std::function<void()> func, std::optional<std::size_t> statckSize = std::nullopt) : m_func(func), m_secondaryFbr(nullptr), m_primaryFbr(nullptr) {
			m_secondaryFbr = CreateFiber(statckSize.has_value() ? statckSize.value() : 0, [](void* param) { static_cast<fbr*>(param)->fbrFunc(); }, this);
		}
		~fbr() {
			if (m_secondaryFbr)
				DeleteFiber(m_secondaryFbr);
		}
	public:
		void tick() {
			m_primaryFbr = GetCurrentFiber();
			if (!m_time.has_value() || m_time.value() <= std::chrono::high_resolution_clock::now())
				SwitchToFiber(m_secondaryFbr);
		}
		void wait(std::optional<std::chrono::high_resolution_clock::duration> time = std::nullopt) {
			if (time.has_value())
				m_time = std::chrono::high_resolution_clock::now() + time.value();
			else
				m_time = std::nullopt;
			SwitchToFiber(m_primaryFbr);
		}
		static fbr* cur() {
			return static_cast<fbr*>(GetFiberData());
		}
	public:
		void fbrFunc() {
			try {
				m_func();
			}
			catch (std::runtime_error& ex) {
			}
			while (true) {
				wait();
			}
		}
	public:
		void* m_primaryFbr;
		void* m_secondaryFbr;
		std::function<void()> m_func;
	public:
		std::optional<std::chrono::high_resolution_clock::time_point> m_time;
	};
	//Script Manager Class
	class fbrMgr {
	public:
		fbrMgr() = default;
		~fbrMgr() = default;
	public:
		void add(std::shared_ptr<fbr> fbr, std::string fbrId) {
			std::lock_guard lck(m_mutex);
			m_scripts.insert({ fbrId, std::move(fbr) });
		}
		void remove(std::string fbrId) {
			if (auto var = m_scripts.find(fbrId); var != m_scripts.end()) {
				m_scripts.erase(fbrId);
			}
			else {
			}
		}
		void removeAll() {
			std::lock_guard lck(m_mutex);
			m_scripts.clear();
		}
		void tick() {
			static bool ensureMainFbr = (ConvertThreadToFiber(nullptr), true);
			std::lock_guard lck(m_mutex);
			for (auto& scr : m_scripts)
				scr.second->tick();
		}
	public:
		std::recursive_mutex m_mutex;
		std::map<std::string, std::shared_ptr<fbr>> m_scripts;
	};
	inline fbrMgr g_FiberManager;
	class fbrPool {
	public:
		fbrPool() = default;
		~fbrPool() = default;
	public:
		void registerFbrPool() {
			for (auto i = 0; i < m_numOfFbrs; ++i)
				g_FiberManager.add(std::make_shared<fbr>([=] { this->fiberFunc(); }), "fbrPool_" + std::to_string(i));
		}
	public:
		void fiberFunc() {
			while (true) {
				tick();
				fbr::cur()->wait();
			}
		}
		void queue(std::function<void()> Func) {
			if (Func) {
				std::lock_guard lck(m_mutex);
				m_jobs.push(std::move(Func));
			}
		}
		void clear() {
			m_jobs.pop();
			
		}
		void tick() {
			std::unique_lock lck(m_mutex);
			if (!m_jobs.empty()) {
				auto job = std::move(m_jobs.top());
				m_jobs.pop();
				lck.unlock();
				std::invoke(std::move(job));
			}
		}
	public:
		std::size_t m_numOfFbrs = 10;
		std::recursive_mutex m_mutex;
		std::stack<std::function<void()>> m_jobs;
	};
	inline fbrPool g_FiberPool;
}