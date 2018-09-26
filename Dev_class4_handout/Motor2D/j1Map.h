#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"



// TODO 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!
// ----------------------------------------------------


// TODO 1: Create a struct needed to hold the information to Map node

enum class orientation { orthogonal, isometric, hexagonal };

enum class renderorder { right_down, right_up, left_down, left_up };

struct mapinfo {

	unsigned int version;
	unsigned int width;
	unsigned int height;
	unsigned int tileheight;
	unsigned int tilewidth;
	//unsigned int orientationnum;
	//unsigned int renderordernum;
	
	orientation mapori;
	renderorder rendord;



	/*unsigned int nextobjectid;*/
};

struct tileset {
	/*unsigned int firstgid;*/

	unsigned int tilewidth;
	unsigned int tileheight;
	unsigned int spacing;
	unsigned int margin;

	p2SString imagename;
	SDL_Texture* source_image;
	unsigned int imagewidth;
	unsigned int imageheight;

};

struct tile {
	unsigned int gid;
};

struct layer {

	p2SString layername;
	unsigned int width;
	unsigned int height;

	p2List <tile> tiles;


};

// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);



private:
	void LoadMapdata();
	tileset LoadTilesetdata(pugi::xml_node );
	layer LoadLayerdata(pugi::xml_node layer);
	tile LoadTile(pugi::xml_node currenttile);

public:

	// TODO 1: Add your struct for map info as public for now

	/*struct mapinfo {};*/
	mapinfo mapdata;

	p2List <tileset>	tilesetlist;

	p2List <layer> layerlist;

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
	
};

#endif // __j1MAP_H__