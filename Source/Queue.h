#pragma once
#include "Natives.hpp"
#include "FiberHelper.hpp"
namespace Saint {
	class Queue {
	public:
		void add(std::optional<std::chrono::high_resolution_clock::duration> time, std::string text, std::function<void()> action = [] {}) {
			
			g_FiberPool.queue([=]
				{
					HUD::BEGIN_TEXT_COMMAND_BUSYSPINNER_ON("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
			HUD::END_TEXT_COMMAND_BUSYSPINNER_ON(3);
			fbr::cur()->wait(time);
			action();
			HUD::BUSYSPINNER_OFF();

				});
		}
		void request_control(Entity entity, std::function<void()> action = [] {}) {
			bool has_control = false;
			if (!has_control) {
				
				g_FiberPool.queue([=]
					{
						HUD::BEGIN_TEXT_COMMAND_BUSYSPINNER_ON("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Requesting control of entity..");
				HUD::END_TEXT_COMMAND_BUSYSPINNER_ON(3);
				fbr::cur()->wait(10ms);
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
				if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity)) {
					HUD::BUSYSPINNER_OFF();
					action();
					
				}

					});
					
					

				
			}
			
			
		}
	};
	inline Queue m_queue;
}