#pragma once
#include <cstring>
#include <vector>
#include "Vector2.h"
#include "Colour.h"
#include "GameObject.h"

//buffer cell is the char and colour for a specific position on the screen
struct BufferCell
{
    char character = ' ';
    WORD colour = ColourCodes[White];

	BufferCell() : character(' '), colour(ColourCodes[White]) {}
	BufferCell(char c, WORD colour) : character(c), colour(colour) {}
};

struct ScreenBuffer 
{
    

    private:

        int row;
        int col;
        std::vector<std::vector<BufferCell>> m_buffer;

        //check if its a valid position
        inline bool inBounds(const int& x, const int& y) const
        {
            return (x >= 0 && x < row && y >= 0 && y < col);
		}

        inline bool inBounds(const Vector2& pos) const
        {
            return (pos.x >= 0 && pos.x < row && pos.y >= 0 && pos.y < col);
		}

    public:

        ScreenBuffer() : row(0), col(0)
        {
            
        }

        ScreenBuffer(const int& x, const int& y) : row(x), col(y) 
        {
            createBuffer(x, y);
        };

        ScreenBuffer(const Vector2& size) : row(size.x), col(size.y)
        {
            createBuffer(size.x, size.y);
        };


        BufferCell& getBufferCell(int x, int y)
        {
            if(!inBounds(x, y))
            {
                throw std::out_of_range("Tried to access position outside of screen buffer");
			}
            return m_buffer[x][y];
        }
    
        void setBufferCell(const int& x, const int& y, char& c, WORD& colour)
        {
            if (inBounds(x, y))
            {
                m_buffer[x][y].character = c;
                m_buffer[x][y].colour = colour;
            }   
        }
    
    
        void setBufferCell(const Vector2& pos, char& c, WORD& colour)
        {
            if (inBounds(pos))
            {
                m_buffer[pos.x][pos.y].character = c;
                m_buffer[pos.x][pos.y].colour = colour;
            }
        }
    
        void setGameObjectAtPos(const GameObject& obj)
        {
            Vector2 pos = obj.getPosition();
            if (inBounds(pos))
            {
                m_buffer[pos.x][pos.y].character = obj.getBody();
				m_buffer[pos.x][pos.y].colour = obj.getColour();
            }    
        }

        //creates a buffer with the amount of cols and rows
        void createBuffer(const int& cols, const int& rows)
        {
			m_buffer.clear();
            m_buffer.reserve(cols);
            for (int i = 0; i < cols; ++i) {
                m_buffer.emplace_back(std::vector<BufferCell>(rows));
                for (int j = 0; j < rows; j++)
                {
                    m_buffer[i][j] = BufferCell();
                }
            }
        }

        //clears the buffer to ' '
        void clearBuffer()
        {
			BufferCell emptyCell;

            for (int i = 0; i < row; i++)
            {
                //changes all the chars in a column given a row index to ' ' 
                std::fill(m_buffer[i].begin(), m_buffer[i].end(), emptyCell);
            }
        }
};
