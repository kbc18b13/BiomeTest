#pragma once

class Perlin
{
public:
    static Perlin& GetInstance(int seed){
        static Perlin instance;
        instance.m_seed = seed;
        return instance;
    }

    static Perlin&  GetInstance()
    {
        static Perlin instance;
        return instance;
    }
private:
    Perlin();
    ~Perlin() {}

public:
    void SetSeed( int seed ){
        m_seed = seed;
    }
    
    int GetSeed(){
       return m_seed;
    }

    float PerlinNoise(float x, float y, float z);
    float OctavePerlin(float x, float y, float z, int octaves, float persistence);
private:
    float Fade(float t)
    {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    unsigned xorshift32( unsigned v ){
        v = v ^ ( v << 13 );
        v = v ^ ( v >> 17 );
        v = v ^ ( v << 15 );
        return v;
    }

    int Hash( float x, float y, float z);

    float Grad(int hash, float x, float y, float z);
    float Lerp(float a, float b, float x)
    {
        return a + x * (b - a);
    }

private:
    int m_seed = 0;
    int m_repeat = -1;
};

static inline Perlin& GetPerlin()
{
    return Perlin::GetInstance();
}