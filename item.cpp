#include "guistuff.cpp"

void sword();
void void_necklace();
void swift_brace();
void lucky_rock();
void item::ItemUse(int id) {

	switch(id) {
	case 0:
		charc->inv->quantity[0] += 1;
		this->name = "Rat Sword";
		this->Description = "A mighty sword that sharpens your damage (Strength +10%)";
		sword();
		break;
	case 1:
		charc->inv->quantity[1] += 1;
		this->name = "Void Necklace";
		this->Description = "A mysterious necklace covered in some black goo (Vitality +10%)";
		void_necklace();
		break;
	case 2:
		charc->inv->quantity[2] += 1;
		this->name = "Speed Brace";
		this->Description = "Supaaaa Fastttt!!!! (Agility +10%)";
		swift_brace();
		break;
	case 3:
		charc->inv->quantity[3] += 1;

		this->name = "Lucky Rock";
		this->Description = "A strange but pleasant rock (Charisma +10%)";
		lucky_rock();
		break;




	}
}
//SOIME WHERE BUGG
//Make make these add onto a multiplier instaed of multiplying everything.
void sword() {
	if (charc->inv->quantity[0] > 1) {
		charc->Player->str /= (((charc->inv->quantity[0] - 1) * 0.1) + 1);
	}
	charc->Player->str *= ((charc->inv->quantity[0] * 0.1) + 1);
}
void void_necklace() {
	//charc->Player->vitalitymult += 0.1;
	if (charc->inv->quantity[1] > 1) {
		charc->Player->vitality /= (((charc->inv->quantity[1] - 1) * 0.1) + 1);
	}
	charc->Player->vitality *= ((charc->inv->quantity[1] * 0.1) + 1);
}
void swift_brace() {
	//charc->Player->Agilitymult +=0.1;
	if (charc->inv->quantity[2] > 1) {
		charc->Player->Agility /= (((charc->inv->quantity[2] - 1) * 0.1) + 1);
	}
	charc->Player->Agility *= ((charc->inv->quantity[2] * 0.1) + 1);
}

void lucky_rock() {
	if (charc->inv->quantity[3] > 1) {
		charc->Player->charisma /= (((charc->inv->quantity[2] - 1) * 0.1) + 1);
	}

	charc->Player->charisma *= ((charc->inv->quantity[2] * 0.1) + 1);
}

void Star_Bringer() {

}