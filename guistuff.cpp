#include "objects.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include <GLFW/glfw3.h>
#include <corecrt_math_defines.h>

// Simple helper function to load an image into a OpenGL texture with common settings




/*----------------------------------------------------------------------------
//TODO
//Add more info
//Add more action pog
//Ui rework
// 
//use console as debugger.
----------------------------------------------------------------------------*/
void levelUpChecker();
void healthChecker();

 inline void statText() {
	 //skeleton text...
	ImGui::Text("Level: %d", charc->level);
	ImGui::Text("Experience: %d/%d", charc->exp,  charc->level * charc->expReq); //(M_PI * charc->level)*charc->expReq);

	ImGui::Text("Gold: %.1f", charc->gold);
	ImGui::Text("Health: %.1f/%.1f", charc->Player->hp, charc->Player->vitality );

	ImGui::Text("Strength: %.1f", charc->Player->str );
	ImGui::Text("Dexterity: %.1f", charc->Player->dex );
	ImGui::Text("Endurance: %.1f", charc->Player->endurance);
	ImGui::Text("Charisma: %.1f", charc->Player->charisma );
	ImGui::Text("Agility: %.1f", charc->Player->Agility);
	ImGui::Text("Critical Chance: %.2f%c", charc->Player->critc, '%');
	ImGui::Text("Critical Damage: %.2f%c", (100*(charc->Player->critd)), '%');
}


 inline void inventoryUi() {
	 //Skeleton Table	
		
	 ImGui::BeginTable("invetory", 1);
	// if (charc->inv->items.size() != NULL) {
		 for (int row = 0; row < charc->inv->items.size(); row++) {
			 ImGui::TableNextRow();
			 
			ImGui::TableSetColumnIndex(0);
			ImGui::Text("%d| %s  ", row,charc->inv->items[row].name.c_str());
			ImGui::Text("%s", charc->inv->items[row].Description.c_str());
			ImGui::Text("ID: % d", charc->inv->items[row].itemID);
		 }

			  // ImGui::TableNextColumn();
			  // ImGui::TableSetupColumn("Description");
			   //ImGui::TableNextRow();
			   //ImGui::Text("Testing");
				   //for (int i = 0; i < charc->inv->items.size(); i++) {
					   //ImGui::Text("%s", charc->inv->items);
				   //}

			 ImGui::EndTable();
		 //}
	// }
 }
	

 