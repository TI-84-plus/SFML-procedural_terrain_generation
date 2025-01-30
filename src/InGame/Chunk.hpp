#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <sys/types.h>
#include "Tile.hpp"
#include <random>
#include "../../libs/FastNoiseLite.h"
class Chunk : public sf::Drawable{
		
	private:
		sf::Texture tileset;
		int seed, seed2, seed3, seed4, seed5;
		int tileTextureDimension = 32;
		double tileWorldDimension = 1;

		float ChunkDimension = 16;
		sf::Vector2f ChunkPosition;

		sf::VertexArray lines;
	
	public:
		sf::VertexArray vertexArray;
		static constexpr float ChunkSize = 16.f;

		Chunk(int seed, sf::Texture& tileset){

		this->seed = seed;
		this->tileset = tileset;
		vertexArray.resize((ChunkSize*2 * ChunkSize*2) * 4);
		vertexArray.setPrimitiveType(sf::Quads);

		lines.resize(ChunkSize*ChunkSize);
		lines.setPrimitiveType(sf::Lines);

        seed2 = modifyseed(seed);
        seed3 = modifyseed(seed2);
        seed4 = modifyseed(seed3);
        seed5 = modifyseed(seed4);
	}

	
	void SetChunkPosition(sf::Vector2f PlayerPosition) {
		
	}

	void TilePosition(int TileX, int TileY, int x, int y, int chunk_x, int chunk_y) 
	{
		Tile tile(TileX, TileY);
		sf::Vector2f tile_pos = {float(x), float(y)};
		sf::Vector2f chunk_pos = {float(chunk_x), float(chunk_y)};

		vertexArray.append(sf::Vertex((((sf::Vector2f(0.0f, 0.0f) + tile_pos) + (chunk_pos * (ChunkSize))) * float(tileWorldDimension)), sf::Vector2f(tileTextureDimension * tile.X + 2 + (tile.X*2), tileTextureDimension * tile.Y + 2 + (tile.Y*2))));

		vertexArray.append(sf::Vertex((((sf::Vector2f(1.0f, 0.0f) + tile_pos) + (chunk_pos * (ChunkSize))) * float(tileWorldDimension)), sf::Vector2f(tileTextureDimension * tile.X + tileTextureDimension + 2 + (tile.X*2), tileTextureDimension * tile.Y + 2 + (tile.Y*2))));

		vertexArray.append(sf::Vertex((((sf::Vector2f(1.0f, 1.0f) + tile_pos) + (chunk_pos * (ChunkSize))) * float(tileWorldDimension)), sf::Vector2f(tileTextureDimension * tile.X + tileTextureDimension + 2 + (tile.X*2), tileTextureDimension * tile.Y + tileTextureDimension + 2 + (tile.Y*2))));

		vertexArray.append(sf::Vertex((((sf::Vector2f(0.0f, 1.0f) + tile_pos) + (chunk_pos * (ChunkSize))) * float(tileWorldDimension)), sf::Vector2f(tileTextureDimension * tile.X + 2 + (tile.X*2), tileTextureDimension * tile.Y + tileTextureDimension + 2 + (tile.Y*2))));



		if(x == -(ChunkSize/2) && y == -(ChunkSize/2)){
			// lines.append(sf::Vertex(sf::Vector2f(-128-8, (-128)+8), sf::Color::Red));
			// lines.append(sf::Vertex(sf::Vector2f((128+8)+1, -128+8), sf::Color::Red));

			// lines.append(sf::Vertex(sf::Vector2f(-128-8, (-128)+16), sf::Color::Red));
			// lines.append(sf::Vertex(sf::Vector2f((128+8)+1, -128+16), sf::Color::Red));

			lines.append(sf::Vertex(sf::Vector2f(-(ChunkSize*ChunkSize/2)-(ChunkSize/2), 	(((-(ChunkSize*ChunkSize/2))+((ChunkSize/2)*(chunk_x+(ChunkSize/2))))+((chunk_x*(ChunkSize/2))+(ChunkSize/2)*(ChunkSize/2)))-(ChunkSize/2)), sf::Color::Red));
			lines.append(sf::Vertex(sf::Vector2f((ChunkSize*(ChunkSize/2))-(ChunkSize/2), (((-(ChunkSize*ChunkSize/2))+((ChunkSize/2)*(chunk_x+(ChunkSize/2))))+((chunk_x*(ChunkSize/2))+((ChunkSize/2)*(ChunkSize/2))))-(ChunkSize/2)), sf::Color::Red));
			std::cout<<((-(ChunkSize*ChunkSize/2))+((ChunkSize/2)*(chunk_x+(ChunkSize/2)))+((chunk_x*(ChunkSize/2))+((ChunkSize/2)*(ChunkSize/2)))) <<std::endl;
		}

		//if(y == ChunkSize/2) {
		//	height_line.setSize(sf::Vector2f(0, ChunkSize));
		//	height_line.setPosition(sf::Vector2f(ChunkSize, (chunk_x*ChunkSize)+0));
		//}
	}


    int modifyseed(int seed)
    {
        std::mt19937 gen(seed);
        return gen();
    }

    FastNoiseLite noiseparams(int oct, double freq, FastNoiseLite::NoiseType type, int seed)
    {
        FastNoiseLite noise;
        noise.SetSeed(seed);
        noise.SetNoiseType(type);
        noise.SetFractalLacunarity(3.0f);
        noise.SetFractalGain(0.5f);
        noise.SetFrequency(freq);
        noise.SetFractalOctaves(oct);
        noise.SetFractalType(noise.FractalType_FBm);
        return noise;
    };

	void ChunkGen(float chunk_x, float chunk_y)
    {
        //NoiseMaps
        FastNoiseLite Layout1= noiseparams(8, 0.00001, FastNoiseLite::NoiseType::NoiseType_OpenSimplex2S, seed);   //Layouts
        FastNoiseLite Layout2= noiseparams(8, 0.00002, FastNoiseLite::NoiseType::NoiseType_OpenSimplex2S, seed2);
        FastNoiseLite Layout3= noiseparams(8, 0.00004, FastNoiseLite::NoiseType::NoiseType_OpenSimplex2S, seed3);
        FastNoiseLite Layout4= noiseparams(8, 0.00008, FastNoiseLite::NoiseType::NoiseType_OpenSimplex2S, seed4);
        FastNoiseLite Layout5= noiseparams(8, 0.000016, FastNoiseLite::NoiseType::NoiseType_OpenSimplex2S, seed5);



		for(int y = -(ChunkDimension)/2; y < ChunkDimension/2; y++) 
		{
			for(int x = -(ChunkDimension/2); x < ChunkDimension/2; x++) 
			{
				double Map1 = Layout1.GetNoise(float((chunk_x*(ChunkSize))+x),float((chunk_y*(ChunkSize)+y)));
        		double Map2 = Layout2.GetNoise(float((chunk_x*(ChunkSize))+x),float((chunk_y*(ChunkSize)+y)));
        		double Map3 = Layout3.GetNoise(float((chunk_x*(ChunkSize))+x),float((chunk_y*(ChunkSize)+y)));
        		double Map4 = Layout4.GetNoise(float((chunk_x*(ChunkSize))+x),float((chunk_y*(ChunkSize)+y)));
        		double Map5 = Layout5.GetNoise(float((chunk_x*(ChunkSize))+x),float((chunk_y*(ChunkSize)+y)));
        		double Layout = Map1 + Map2 + Map3 + Map4 + Map5;
        		Layout = (Layout + 1.0) / 2.0;
        		Layout = int(Layout * 255);
				

				if (Layout < 100)
				{
					TilePosition(4, 0, x, y, chunk_x, chunk_y);
				}

				else if (Layout < 120) 
				{
					TilePosition(3, 0, x, y, chunk_x, chunk_y);
				}

				else
				{
					//Sand
                    if(Layout < 160)
                    {
						TilePosition(2, 0, x, y, chunk_x, chunk_y);
                    }
					//Shallow Forest
                    else if(Layout < 190)
                    {
						TilePosition(0, 0, x, y, chunk_x, chunk_y);
                    }
					//Dense forest
                    else if(Layout < 250) 
                    {
						TilePosition(1, 0, x, y, chunk_x, chunk_y);
                    }
					//Shallow dirt
                    else if(Layout < 285) 
                    {
						TilePosition(5, 0, x, y, chunk_x, chunk_y);
                    }
					//Dense Dirt
                    else if(Layout < 300) 
                    {
						TilePosition(6, 0, x, y, chunk_x, chunk_y);
                    }
					//Mountains
                    else if(Layout < 320)
                    {
						TilePosition(0, 1, x, y, chunk_x, chunk_y);
                    }
					//Dense Snow
                    else
                    {

						TilePosition(1, 1, x, y, chunk_x, chunk_y);
                    }
                }
			}
		}

	}
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		states.texture = &tileset;
		target.draw(vertexArray, states);
		target.draw(lines);
		// std::cout<<tileset.getSize().y<<std::endl;
	}
};

#endif
