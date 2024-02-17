#pragma once

using Any = int;
using Hash = std::uint32_t;
using Entity = std::int32_t;
using Player = std::int32_t;
using FireId = std::int32_t;
using Interior = std::int32_t;
using Ped = Entity;
using Vehicle = Entity;
using Cam = std::int32_t;
using Object = Entity;
using Pickup = Object;
using Blip = std::int32_t;
using Camera = Entity;
using ScrHandle = Entity;



#pragma pack(push, 1)
	struct Vector2
	{
		float x{};
		float y{};
	};
#pragma pack(pop)
#pragma pack(push, 1)
    class PostInt
    {
    public:

       
        PostInt() = default;

        PostInt(int original, int changed, int min, int max) :
            original(original), changed(changed), min(min), max(max)
        {}

        PostInt operator+(const PostInt& other)
        {
            PostInt vec;
            vec.original = this->original + other.original;
            vec.changed = this->changed + other.changed;
            vec.min = this->min + other.min;
            vec.max = this->max + other.max;
            return vec;
        }

        PostInt operator-(const PostInt& other)
        {
            PostInt vec;
            vec.original = this->original - other.original;
            vec.changed = this->changed - other.changed;
            vec.min = this->min - other.min;
            vec.max = this->max - other.max;
            return vec;
        }

        PostInt operator*(const PostInt& other)
        {
            PostInt vec;
            vec.original = this->original * other.original;
            vec.changed = this->changed * other.changed;
            vec.min = this->min * other.min;
            vec.max = this->max * other.max;
            return vec;
        }

        PostInt operator*(const float& other)
        {
            PostInt vec;
            vec.original = this->original * other;
            vec.changed = this->changed * other;
            vec.min = this->min * other;
            vec.max = this->max * other;
            return vec;
        }
    public:
        float original{};
    private:
        char m_padding1[0x04];
    public:
        float changed{};
    private:
        char m_padding2[0x04];
    public:
        float min{};
    private:
        char m_padding3[0x04];
    public:
        float max{};
    private:
        char m_padding4[0x04];
    };
#pragma pack(pop)
#pragma pack(push, 1)
    class NativeVector3
    {
    public:
        NativeVector3() = default;

        NativeVector3(float x, float y, float z) :
            x(x), y(y), z(z)
        {}

        NativeVector3 operator+(const NativeVector3& other)
        {
            NativeVector3 vec;
            vec.x = this->x + other.x;
            vec.y = this->y + other.y;
            vec.z = this->z + other.z;
            return vec;
        }

        NativeVector3 operator-(const NativeVector3& other)
        {
            NativeVector3 vec;
            vec.x = this->x - other.x;
            vec.y = this->y - other.y;
            vec.z = this->z - other.z;
            return vec;
        }

        NativeVector3 operator*(const NativeVector3& other)
        {
            NativeVector3 vec;
            vec.x = this->x * other.x;
            vec.y = this->y * other.y;
            vec.z = this->z * other.z;
            return vec;
        }

        NativeVector3 operator*(const float& other)
        {
            NativeVector3 vec;
            vec.x = this->x * other;
            vec.y = this->y * other;
            vec.z = this->z * other;
            return vec;
        }
    public:
        float x{};
    private:
        char m_padding1[0x04];
    public:
        float y{};
    private:
        char m_padding2[0x04];
    public:
        float z{};
    private:
        char m_padding3[0x04];
    };
#pragma pack(pop)
struct CoordStats {
    int hours;
    int minutes;
    int seconds;
    float distance;
};
#pragma pack(push, 1)
	struct Vector3
	{
		float x{};
		float y{};
		float z{};
	};
#pragma pack(pop)
#pragma pack(push, 1)
    struct ImageDimensions
    {
        int x, y;
        ImageDimensions() { x = y = 0; }
        ImageDimensions(int _x, int _y) { x = _x; y = _y; }
    };
#pragma pack(pop)
#pragma pack(push, 1)
	struct Color
	{
        int r{ 255 };
        int g{ 255 };
        int b{ 255 };
		int a{ 255 };
	};
#pragma pack(pop)