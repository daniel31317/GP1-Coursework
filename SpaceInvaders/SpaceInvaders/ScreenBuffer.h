#pragma once
#include "Vector2.h"

struct ScreenBuffer {
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
        for (int i = 0; i < col; i++)
        {
            delete[] m_buffer[i];
        }
        delete[] m_buffer;
    }

    char& getChar(int x, int y) const
    {
        return m_buffer[x][y];
    }
    
    void setChar(char c, int x, int y)
    {
        m_buffer[x][y] = c;
    }
    
    
    void setChar(char c, Vector2 pos)
    {
        m_buffer[pos.x][pos.y] = c;
    }
    
    void setGameObjectAtPos(const GameObject& obj)
    {
        Vector2 pos = obj.getPosition();
        m_buffer[pos.x][pos.y] = obj.getbody();
    }

    void createBuffer(int cols, int rows)
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
            for (int j = 0; j < col; j++)
            {
                m_buffer[i][j] = ' ';
            }
        }
    }

    ScreenBuffer& operator=(ScreenBuffer&& other) noexcept //Move Assignment Operator
    {
        if (this != &other) {
            // Deallocate existing memory
            for (int i = 0; i < row; ++i) {
                delete[] m_buffer[i];
            }
            delete[] m_buffer;

            // Transfer ownership
            row = other.row;
            col = other.col;
            m_buffer = other.m_buffer;

            // Reset the source object
            other.row = 0;
            other.col = 0;
            other.m_buffer = nullptr;
        }
        return *this;
    }


private:
    int row;
    int col;
    char** m_buffer;
};
