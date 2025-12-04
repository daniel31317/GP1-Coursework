#pragma once
#include <cstring>
#include "Vector2.h"

struct ScreenBuffer 
{

    private:
        int row;
        int col;
        std::vector<std::vector<char>> m_buffer;


    public:

        ScreenBuffer() : row(0), col(0)
        {
            
        }

        ScreenBuffer(int x, int y) : row(x), col(y) 
        {
            createBuffer(x, y);
        };

        ScreenBuffer(Vector2 size) : row(size.x), col(size.y)
        {
            createBuffer(size.x, size.y);
        };


        char& getChar(int x, int y)
        {
            return m_buffer[x][y];
        }
    
        void setChar(const char c, const int x, const int y)
        {
            m_buffer[x][y] = c;
        }
    
    
        void setChar(const char c, const Vector2 pos)
        {
            m_buffer[pos.x][pos.y] = c;
        }
    
        void setGameObjectAtPos(const GameObject& obj)
        {
            Vector2 pos = obj.getPosition();
            m_buffer[pos.x][pos.y] = obj.getBody();
        }

        void createBuffer(const int cols, const int rows)
        {
			m_buffer.clear();
            m_buffer.resize(cols);
            for (int i = 0; i < cols; ++i) {
                m_buffer[i] = std::vector<char>(rows);
                for (int j = 0; j < rows; j++)
                {
                    m_buffer[i][j] = ' ';
                }
            }
        }

        void clearBuffer()
        {
            for (int i = 0; i < row; i++)
            {
                //changes all the chars in a column given a row index to ' ' 
                std::fill(m_buffer[i].begin(), m_buffer[i].end(), ' ');
            }
        }
};
