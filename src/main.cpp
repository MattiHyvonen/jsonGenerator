#include "jsonGenerator.h"
#include <vector>
#include <fstream>

int main(int argc, char** argv) {

	std::ofstream file;
	file.open("file.json");
	if (!file.is_open() )
		return 1;

	pair_json nimi("nimi", "viiva_2017-9-16_16-55-42");
	pair_json sarjan_nimi("sarjan_nimi", "viiva_ja_vari_2017-9-16_n1");
	pair_json kalibroinnin_vari("kalibroinnin_vari", rgb_json(255, 0, 200) );
	pair_json kalibroinnin_paksuus("kalibroinnin_paksuus", 0.65);
	pair_json kalibroinnin_sumeus("kalibroinnin_sumeus", 0.91);

	array_json siivut;
	object_json siivuObject;
	pair_json paikka("paikka", vec2_json(640, 480));
	pair_json paine("paine", 0.9987);
	siivuObject.add(paikka);
	siivuObject.add(paine);
	siivut.add(siivuObject);
	siivut.add(siivuObject);
	siivut.add(siivuObject);

	pair_json siivutPair("siivut", siivut);

	object_json viiva;
	viiva.add(nimi);
	viiva.add(sarjan_nimi);
	viiva.add(kalibroinnin_vari);
	viiva.add(kalibroinnin_paksuus);
	viiva.add(kalibroinnin_sumeus);
	viiva.add(siivutPair);

	//std::cout << viiva.stringify() << "\n";
	file << viiva.stringify() << "\n";
	file.close();
	return 0;
}