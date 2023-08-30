#pragma 

#include <bits/stdc++.h>
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include <Windows.h>
#include <cstdlib>
#include <GLFW/glfw3.h>
/*----------------------------------------------------------------------------
//TODO
//Stat reworks please
//figure somethngs out with charisma
//when characters have very high of one stat give them a special passive 
//Leveling for players don't do anything
//Make leveling give increase of a random stat by a 20 percent
//
//Make things less random 
//Throw exception for image

----------------------------------------------------------------------------*/

template <typename T>
void remove(std::vector<T>& v, size_t index) {
	v.erase(v.begin() + index);
}




class entity {
public:
	int level = 1;
	double dex = 0;
	double str = 0;
	double endurance = 0;
	double charisma = 0;
	double hp = 0;
	double vitality = 0;
	double critc = 0;
	double critd = 0;
	double Agility = 0;

	int name;
};

class encounterWindow {
	encounterWindow();

};
class encounter {
public:
	bool elite = false;
	encounter(int level);
	entity* enemy;
	void fight();
	bool endBattle = false;
	bool statsMade = false;
};
class game {
public:
	entity* player;
	//encounter* encounter;
	void battle(encounter* enemy);
};
class item {
public:
	std::string name;
	std::string Description;
	int itemID; //In a array of functions this ID will formulate what function will be the use of the item
	//we will use a sword for example as id:0
	void ItemUse(int id);
	item(int id) {
		this->name = name;
		this->itemID = id;
		ItemUse(id);
	}
};

class inventory {
public:
	std::vector<item> items; //Make into map, make it so dupes are left in stacks and have stacks be used to calculated multiplier so they don't get out of control
	int quantity[5] = { 0,0,0,0,0 }; ///how many of a item is here
		//the number in the brackets represent the id!!

							 
	//something like this
	//str / (((quantity-1)  * 0.1) + 1) ONLY DO THIS WHEN YOU HAVE AT LEAST ONE ITEM OR ELSE IT WILL DIVIDE BY ZERO 
	//str * ((quantity * 0.1) + 1)
}; 
class character  {
public:
	character() {
		this->inv = new inventory;
	}
	inventory* inv;


	int level=1;
	int gold=0;
	int exp=0;
	int expReq=40;
	entity* Player = NULL;
}; 





class Player {
public:
	Player();
};


class globalValue {
public:
	game* Game;
};




class encounterDisplay {
public:
	encounterDisplay(int playlevel, GLFWwindow* window) {
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		this->enemy = new encounter(((rand() % 5 )+ 1) + playlevel);
		this->Position = ImVec2(rand() % width, rand() % height);
	}
	~encounterDisplay() {
		this->closeWindow = true;
	}
	void EncounterDisplayer(int i) {
		if (!closeWindow) {

			std::ostringstream EncounterStream;
			std::string EncounterName = "Encounter!##";
			EncounterStream << i;
			EncounterName.append(EncounterStream.str());
			ImGui::Begin(EncounterName.c_str());
			if (!settingsDone) {
				ImGui::SetWindowPos(Position);
				ImGui::SetWindowSize(Size);
				settingsDone = true;

			}
			if (this->enemy->elite) {
				ImGui::Text("ELITE %s Level: %d ", EnemyTypes[this->enemy->enemy->name].c_str(), this->enemy->enemy->level);

			}
			else {
				ImGui::Text("%s Level: %d ", EnemyTypes[this->enemy->enemy->name].c_str(), this->enemy->enemy->level);
			}
			ImGui::Text("Health: %.1f/%.1f", this->enemy->enemy->hp, this->enemy->enemy->vitality);
			ImGui::Text("Strength: %.1f", this->enemy->enemy->str);
			ImGui::Text("Dexterity: %.1f", this->enemy->enemy->dex);
			ImGui::Text("Endurance: %.1f", this->enemy->enemy->endurance);
			ImGui::Text("Charisma: %.1f", this->enemy->enemy->charisma);
			ImGui::Text("Agility: %.1f", this->enemy->enemy->Agility);
			ImGui::Text("Critical Chance: %.2f%c", this->enemy->enemy->critc, '%');
			ImGui::Text("Critical Damage: %.2f%c", (100 * (this->enemy->enemy->critd)), '%');
			if (EnemyTypes[this->enemy->enemy->name] == "RAT") {
				ImGui::Text("    @@@ **@@@@                                 \n    *******@@                                  \n   ** #  # ***                          +----- \n   *--    ---******                     |      \n    *--   --      *******               |      \n      ***               ****            |      \n        **                 ***--+--+    |      \n         ***                **     |    |      \n         | ******          *|      +-+--+      \n        --   |   **********--                  \n             |            |                    \n           ---          ---                     ");
			}
			else if (EnemyTypes[this->enemy->enemy->name] == "Worm") {
				ImGui::Text("            *----*                       \n         *---    -- *                    \n         -- @@  @@----- *                \n         -  @@  @@--  ---*               \n         --       --   ##---             \n         *---    --  ###   --            \n          *----------#--    --           \n                      *-#### -           \n                   ***--   ##-           \n                 *-##--    ---           \n           -------- #####-----------     \n          --    ####--*   #    #  ---    \n          ---    #       #---------      \n           --------------     ");
			}
			else if (EnemyTypes[this->enemy->enemy->name] == "Virus") {
				ImGui::Text("       $  $  $ $                            \n    $  #  #  # #  $                         \n  $  # ######### #  $                       \n   # ##***     *## #                        \n    #**----- --- *#                         \n  $##   |     |  *##$                       \n    #             #                         \n  $##    ####     ##$                       \n    #             #                         \n  $##&&         &&##$                       \n     ##&&     &&&#                          \n    #  #########  #                         \n   $  #  #   #  #  $                        \n     $   $   $   $       ");
			}
			else if (EnemyTypes[this->enemy->enemy->name] == "Warthog") {
				ImGui::Text("       %%%%                                 \n      %%%%%%%%%%###                  --+       \n       %%%%%%%%%% ##                   |       \n       #%%%%%%%%  ####   #######      |       \n  &   #@@        ######### ##-----+       \n  && ###                   $#             \n  &#####$$             $$$###             \n    ########## $$$$$$$#####               \n         ##   ########   ##               \n        $#             $###               ");
			}
			else if ((EnemyTypes[this->enemy->enemy->name] == "Fairy")) {
				ImGui::Text("\n +                     +       \n \\\\+                 +//       \n  \\\\\\\\+    ***    +////        \n  / \\\\\\\\+ *@@@* +//// \\        \n    /\\\\\\\\*@***@*////\\          \n      \\\\\\@*&*&*@///            \n      / \\@**$**@/ \\            \n         \\@***@/               \n          \\@@@/                ");
			}
			if (ImGui::Button("Fight")) {
				this->enemy->fight();
			}
			//std::cout << this->enemy->endBattle << "\n";
			if (this->enemy->endBattle) {
				this->closeWindow = true;
				//delete this;
				//EncounterVec.erase(EncounterVec.begin() + this->Index);

				//std::cout << "DEAD" << index << '\n';
			}
			ImGui::End();
		}
	}
	std::string EnemyTypes[5] = { "RAT", "Worm", "Virus", "Warthog", "Fairy" };


	bool settingsDone = false;
	ImVec2 Position;
	ImVec2 Size = ImVec2(300,400);
	int Index = NULL;
	bool closeWindow = false;
	encounter* enemy;
};
