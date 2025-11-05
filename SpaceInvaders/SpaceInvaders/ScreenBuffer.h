#pragma once
#include <cstring>

struct ScreenBuffer 
{

    private:
        int row;
        int col;
        char** m_buffer;

    public:

        ScreenBuffer() : row(0), col(0)
        {
            m_buffer = nullptr;
        }

        ScreenBuffer(int x, int y) : row(x), col(y) 
        {
            createBuffer(x, y);
        };

        ~ScreenBuffer() 
        {
            for (int i = 0; i < row; i++)
            {
                delete[] m_buffer[i];
            }
            delete[] m_buffer;
        }

        char& getChar(int x, int y) const
        {
            return m_buffer[x][y];
        }
    
        void setChar(const char& c, const int x, const int y)
        {
            m_buffer[x][y] = c;
        }
    
    
        void setChar(const char& c, const Vector2 pos)
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
            m_buffer = new char* [row];
            for (int i = 0; i < row; ++i) {
                m_buffer[i] = new char[col];
                for (int j = 0; j < col; j++)
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
                memset(m_buffer[i], ' ', col);
            }
        }
};
