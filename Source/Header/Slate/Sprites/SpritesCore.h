#pragma once

#include <string>

struct Vector2 {
	int X, Y;
	static const Vector2 Zero;
	Vector2() : X(0), Y(0) {}
	Vector2(int X, int Y) : X(X), Y(Y) {}

	inline Vector2 operator+(const Vector2& other) const {
		return Vector2(X + other.X, Y + other.Y);
	}
	inline Vector2 operator-(const Vector2& other) const {
		return Vector2(X - other.X, Y - other.Y);
	}
	inline Vector2 operator-() const { return Vector2(-X, -Y); }
	inline Vector2 operator*(const double& scale) const {
		return Vector2((int)(X * scale + 0.5), (int)(Y * scale + 0.5));
	}
	inline Vector2 operator/(const double& scale) const {
		return Vector2((int)(X / scale + 0.5), (int)(Y / scale + 0.5));
	}

	// Compound assignment operators
	inline Vector2& operator+=(const Vector2& other) {
		X += other.X; Y += other.Y; return *this;
	}
	inline Vector2& operator-=(const Vector2& other) {
		X -= other.X; Y -= other.Y; return *this;
	}
	inline Vector2& operator*=(double scale) {
		X = (int)(X * scale + 0.5);
		Y = (int)(Y * scale + 0.5);
		return *this;
	}
	inline Vector2& operator/=(double scale) {
		X = (int)(X / scale + 0.5);
		Y = (int)(Y / scale + 0.5);
		return *this;
	}

	// Comparison operators
	inline bool operator==(const Vector2& other) const {
		return X == other.X && Y == other.Y;
	}
	inline bool operator!=(const Vector2& other) const {
		return !(*this == other);
	}
};


class ISprite {
protected:
	Vector2 Location = Vector2::Zero, Size = Vector2::Zero;

public:
	ISprite(int LocationX, int LocationY, int Width, int Height)
		: Location(LocationX, LocationY)
		, Size(Width, Height) {
	}

	ISprite(Vector2 Location, Vector2 Size)
		: Location(Location), Size(Size) {
	}

	virtual ~ISprite() = default;
	virtual void Render() = 0;
};


class SRectFilled : public ISprite {
protected:
	std::string RenderChar;
public:
	SRectFilled(int LocationX, int LocationY,
		int Width, int Height, std::string RenderWith = "#")
		: ISprite(LocationX, LocationY, Width, Height)
		, RenderChar(RenderWith) {
	}

	SRectFilled(Vector2 Location, Vector2 Size,
		std::string RenderWith = "#")
		: ISprite(Location, Size), RenderChar(RenderWith) {
	}

	virtual void Render() override;
};


class SRectWireframe : public ISprite {
public:
	SRectWireframe(int LocationX, int LocationY, int Width, int Height)
		: ISprite(LocationX, LocationY, Width, Height) {
	}

	SRectWireframe(Vector2 Location, Vector2 Size,
		std::string RenderWith = "#") : ISprite(Location, Size) {
	}

	virtual void Render() override;
};


class STextBox : public ISprite {
protected:
	std::string Text;
	bool bWrapText;
	bool bClipText;
public:
	STextBox(int LocationX, int LocationY,
		int Width, int Height, const std::string& InText,
		bool bInWrapText = true, bool bInClipText = false)
		: ISprite(LocationX, LocationY, Width, Height)
		, Text(InText)
		, bWrapText(bInWrapText)
		, bClipText(bInClipText) {
	}

	STextBox(Vector2 Location, Vector2 Size, const std::string& InText,
		bool bInWrapText = true, bool bInClipText = false)
		: ISprite(Location, Size), Text(InText)
		, bWrapText(bInWrapText), bClipText(bInClipText) {
	}

	virtual void Render() override;
};