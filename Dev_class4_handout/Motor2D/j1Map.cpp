#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;

	for (p2List_item <tileset> *aux = tilesetlist.start; aux ; aux = tilesetlist.start->next)
	{
		App->render->Blit(aux->data.source_image, 0, 0);
	}

	// TODO 6: Iterate all tilesets and draw all their 
	// images in 0,0 (you should have only one tileset for now)

}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map


	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	if(ret == true)
	{
		// TODO 3: Create and call a private function to load and fill
		// all your map data
		LoadMapdata();
	}

	

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!
	for (pugi::xml_node tileset = map_file.child("map").child("tileset"); tileset; tileset = tileset.next_sibling("tileset"))
	{
		tilesetlist.add(LoadTilesetdata(tileset));
		
	}

	

	//Loading all layers
	for (pugi::xml_node layernode = map_file.child("map").child("layer"); layernode; layernode = layernode.next_sibling("layer"))
	{
		layerlist.add(LoadLayerdata(layernode));
		
	}


	if(ret == true)
	{
		LOG("Successfully parsed map XML file: hello2.tmx");
	/*	tilesetlist*/
		// TODO 5: LOG all the data loaded
		// iterate all tilesets and LOG everything
	}

	map_loaded = ret;

	return ret;
}

void j1Map::LoadMapdata()
{
	mapdata.version = map_file.child("map").attribute("version").as_uint();
	LOG("mapdata version %i", mapdata.version);

	mapdata.width = map_file.child("map").attribute("width").as_uint();
	LOG("mapdata width %i", mapdata.width);

	mapdata.height = map_file.child("map").attribute("height").as_uint();
	LOG("mapdata height %i", mapdata.height);

	mapdata.tilewidth = map_file.child("map").attribute("tilewidth").as_uint();
	LOG("mapdata tilewidth %i", mapdata.tilewidth);

	mapdata.tileheight = map_file.child("map").attribute("tileheight").as_uint();
	LOG("mapdata tileheight %i", mapdata.tileheight);

	const char * orient;
	orient = map_file.child("map").attribute("orientation").as_string();

	if (SDL_strcmp(orient, "orthogonal") == 0)
	{
		mapdata.mapori = orientation::orthogonal;
	}
	else if (SDL_strcmp(orient, "isometric") == 0)
	{
		mapdata.mapori = orientation::isometric;
	}
	else
	{
		mapdata.mapori = orientation::hexagonal;
	}

	LOG("mapdata orientation %i", mapdata.mapori);

	const char * rendorder;
	rendorder = map_file.child("map").attribute("renderorder").as_string();

	if (SDL_strcmp(rendorder, "right-down") == 0)
	{
		mapdata.rendord = renderorder::right_down ;
	}
	else if (SDL_strcmp(rendorder, "right-up") == 0)
	{
		mapdata.rendord = renderorder::right_up;
	}
	else if (SDL_strcmp(rendorder, "left-down") == 0)
	{
		mapdata.rendord = renderorder::left_down;
	}
	else
	{
		mapdata.rendord = renderorder::left_up;
	}

	LOG("render order %i", mapdata.rendord);
	
}

tileset j1Map::LoadTilesetdata (pugi::xml_node tilesetnode)
{

	tileset tilesetdata;

	pugi::xml_node img = map_file.child("map");

	tilesetdata.tilewidth= tilesetnode.attribute("tilewidth").as_uint();
	LOG("tileset tilewidth %i", tilesetdata.tilewidth);

	tilesetdata.tileheight = tilesetnode.attribute("tileheight").as_uint();
	LOG("tileset tileheight %i", tilesetdata.tileheight);

	tilesetdata.spacing = tilesetnode.attribute("spacing").as_uint();
	LOG("tileset spacing %i", tilesetdata.spacing);

	tilesetdata.margin = tilesetnode.attribute("margin").as_uint();
	LOG("tileset margin %i", tilesetdata.margin);


	tilesetdata.imagename = tilesetnode.child("image").attribute("source").as_string();
	LOG("tileset imagename %s", tilesetdata.imagename.GetString());

	p2SString imagepath("%s%s", folder.GetString(), tilesetdata.imagename.GetString());
	LOG("imagepath is %s", imagepath.GetString());

	tilesetdata.source_image = App->tex->Load(imagepath.GetString());

	tilesetdata.imagewidth = tilesetnode.child("image").attribute("width").as_uint();
	LOG("image width %i", tilesetdata.imagewidth);

	tilesetdata.imageheight = tilesetnode.child("image").attribute("height").as_uint();
	LOG("image height %i", tilesetdata.imageheight);


	return tilesetdata;
}

layer j1Map::LoadLayerdata(pugi::xml_node layernode) {

	layer aux;

	aux.layername = layernode.attribute("name").as_string();
	LOG("layer name %s", aux.layername.GetString());

	aux.width = layernode.attribute("width").as_uint();
	LOG("layer width %i", aux.width);

	aux.height = layernode.attribute("height").as_uint();
	LOG("layer height %i", aux.height);

	
	for (pugi::xml_node tile = layernode.child("data").first_child(); tile; tile = tile.next_sibling())
	{
		aux.tiles.add(LoadTile(tile));
	}

	return aux;
}

tile j1Map::LoadTile(pugi::xml_node currenttile) {

	tile aux;

	aux.gid = currenttile.attribute("gid").as_uint();
	LOG("tile gid %i", aux.gid);


	return aux;
}


