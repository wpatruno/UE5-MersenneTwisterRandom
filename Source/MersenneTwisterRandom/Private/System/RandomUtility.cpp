// Fill out your copyright notice in the Description page of Project Settings.


#include "System/RandomUtility.h"


RandomUtility::RandomUtility(): Engine(RandomEngine::StaticNewSeed())
{
}

RandomUtility::RandomUtility(int32 InSeed): Engine(InSeed)
{
}

RandomUtility::~RandomUtility()
{
}

int32 RandomUtility::GetSeed() const
{
	return Engine.GetRootSeed();
}

FColor RandomUtility::RandColor()
{
	// Generate random RGBA components (0-255)
	const uint8 R = static_cast<uint8>(Engine.RandInt(0, 255));
	const uint8 G = static_cast<uint8>(Engine.RandInt(0, 255));
	const uint8 B = static_cast<uint8>(Engine.RandInt(0, 255));

	return FColor(R, G, B);
}

FColor RandomUtility::RandColorAlpha()
{
	// Generate random RGBA components (0-255)
	const uint8 R = static_cast<uint8>(Engine.RandInt(0, 255));
	const uint8 G = static_cast<uint8>(Engine.RandInt(0, 255));
	const uint8 B = static_cast<uint8>(Engine.RandInt(0, 255));
	const uint8 A = static_cast<uint8>(Engine.RandInt(0, 255));

	return FColor(R, G, B, A);
}

FVector RandomUtility::RandVector(const float Min, const float Max)
{
	// Generate random X, Y, Z components within the specified range
	const float X = Engine.RandFloat(Min, Max);
	const float Y = Engine.RandFloat(Min, Max);
	const float Z = Engine.RandFloat(Min, Max);

	return FVector(X, Y, Z);
}

FVector RandomUtility::RandVectorNormalized()
{
	// Generate a random vector and normalize it to unit length
	// Using spherical coordinates to ensure uniform distribution on unit sphere
	const float Theta = Engine.RandFloat(0.0f, 2.0f * PI); // Azimuth angle (0 to 2π)
	const float CosPhiPolar = Engine.RandFloat(-1.0f, 1.0f); // Cosine of polar angle (-1 to 1)

	// Use sqrt(1 - cos²(φ)) instead of sin(acos(cos(φ))) for better numerical stability
	const float SinPhiPolar = FMath::Sqrt(1.0f - CosPhiPolar * CosPhiPolar);

	const float X = SinPhiPolar * FMath::Cos(Theta);
	const float Y = SinPhiPolar * FMath::Sin(Theta);
	const float Z = CosPhiPolar;

	return FVector(X, Y, Z);
}

FVector2D RandomUtility::RandVector2D(const float Min, const float Max)
{
	// Generate random X, Y components within the specified range
	const float X = Engine.RandFloat(Min, Max);
	const float Y = Engine.RandFloat(Min, Max);

	return FVector2D(X, Y);
}

FVector2D RandomUtility::RandVector2DNormalized()
{
	// Generate a random unit vector (length = 1.0) on the unit circle
	const float Angle = Engine.RandFloat(0.0f, 2.0f * PI);

	const float X = FMath::Cos(Angle);
	const float Y = FMath::Sin(Angle);

	return FVector2D(X, Y);
}

FVector2D RandomUtility::RandVector2DInCircle(const float Radius)
{
	// Generate a random point inside a circle using rejection sampling for uniform distribution
	const float Angle = Engine.RandFloat(0.0f, 2.0f * PI);
	const float R = FMath::Sqrt(Engine.RandFloat(0.0f, 1.0f)) * Radius;

	const float X = R * FMath::Cos(Angle);
	const float Y = R * FMath::Sin(Angle);

	return FVector2D(X, Y);
}

FVector2D RandomUtility::RandVector2DOnCircle(const float Radius)
{
	// Generate a random point on the circumference of a circle
	const float Angle = Engine.RandFloat(0.0f, 2.0f * PI);

	const float X = FMath::Cos(Angle);
	const float Y = FMath::Sin(Angle);

	return FVector2D(X, Y) * Radius;
}

FVector RandomUtility::RandPointInSphere(const float Radius)
{
	// Generate a random point inside a sphere using spherical coordinates
	const float Theta = Engine.RandFloat(0.0f, 2.0f * PI); // Azimuth angle
	const float CosPhiPolar = Engine.RandFloat(-1.0f, 1.0f); // Cosine of polar angle
	const float R = FMath::Pow(Engine.RandFloat(0.0f, 1.0f), 1.0f / 3.0f); // Cube root for uniform distribution

	// Use sqrt(1 - cos²(φ)) instead of sin(acos(cos(φ))) for better numerical stability
	const float SinPhiPolar = FMath::Sqrt(1.0f - CosPhiPolar * CosPhiPolar);

	// Generate unit vector, then scale by random radius
	const FVector UnitVector(
		SinPhiPolar * FMath::Cos(Theta),
		SinPhiPolar * FMath::Sin(Theta),
		CosPhiPolar
	);

	return UnitVector * (R * Radius);
}

FVector RandomUtility::RandPointOnSphere(const float Radius)
{
	// Generate a random point on the surface of a sphere
	const float Theta = Engine.RandFloat(0.0f, 2.0f * PI); // Azimuth angle
	const float CosPhiPolar = Engine.RandFloat(-1.0f, 1.0f); // Cosine of polar angle

	// Use sqrt(1 - cos²(φ)) instead of sin(acos(cos(φ))) for better numerical stability
	const float SinPhiPolar = FMath::Sqrt(1.0f - CosPhiPolar * CosPhiPolar);

	// Generate unit vector, then scale by radius
	const FVector UnitVector(
		SinPhiPolar * FMath::Cos(Theta),
		SinPhiPolar * FMath::Sin(Theta),
		CosPhiPolar
	);

	return UnitVector * Radius;
}

FVector RandomUtility::RandPointInCircle(const float Radius)
{
	// Generate a random point inside a circle in the XY plane (Z = 0)
	const FVector2D Point2D = RandVector2DInCircle(Radius);
	return FVector(Point2D.X, Point2D.Y, 0.0f);
}

FVector RandomUtility::RandPointOnCircle(const float Radius)
{
	// Generate a random point on the circumference of a circle in the XY plane (Z = 0)
	const FVector2D Point2D = RandVector2DOnCircle(Radius);
	return FVector(Point2D.X, Point2D.Y, 0.0f);
}

FQuat RandomUtility::RandQuat()
{
	// Generate a random quaternion using Shoemake's method for uniform distribution
	const float U1 = Engine.RandFloat(0.0f, 1.0f);
	const float U2 = Engine.RandFloat(0.0f, 2.0f * PI);
	const float U3 = Engine.RandFloat(0.0f, 2.0f * PI);

	const float SqrtU1 = FMath::Sqrt(U1);
	const float Sqrt1MinusU1 = FMath::Sqrt(1.0f - U1);

	const float X = Sqrt1MinusU1 * FMath::Sin(U2);
	const float Y = Sqrt1MinusU1 * FMath::Cos(U2);
	const float Z = SqrtU1 * FMath::Sin(U3);
	const float W = SqrtU1 * FMath::Cos(U3);

	return FQuat(X, Y, Z, W);
}

FRotator RandomUtility::RandRotator()
{
	// Generate random Pitch, Yaw, and Roll values
	// Pitch: -90 to 90 degrees (up/down)
	// Yaw: -180 to 180 degrees (left/right)
	// Roll: -180 to 180 degrees (rotation around forward axis)
	const float Pitch = Engine.RandFloat(-90.0f, 90.0f);
	const float Yaw = Engine.RandFloat(-180.0f, 180.0f);
	const float Roll = Engine.RandFloat(-180.0f, 180.0f);

	return FRotator(Pitch, Yaw, Roll);
}

template <typename T>
T RandomUtility::RandArrayElement(const TArray<T>& Array)
{
	if (Array.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("RandomUtility::RandArrayElement - Array is empty"));
		return T{};
	}

	const int32 RandomIndex = Engine.RandInt(0, Array.Num() - 1);
	return Array[RandomIndex];
}

template <typename T>
void RandomUtility::ShuffleArray(TArray<T>& Array)
{
	// Fisher-Yates shuffle algorithm
	for (int32 i = Array.Num() - 1; i > 0; --i)
	{
		const int32 j = Engine.RandInt(0, i);
		Array.Swap(i, j);
	}
}

UObject* RandomUtility::RandArrayElementObject(const TArray<UObject*>& Array)
{
	if (Array.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("RandomUtility::RandArrayElementObject - Array is empty"));
		return nullptr;
	}

	const int32 RandomIndex = Engine.RandInt(0, Array.Num() - 1);
	return Array[RandomIndex];
}

void RandomUtility::ShuffleArrayObject(TArray<UObject*>& Array)
{
	// Fisher-Yates shuffle algorithm for UObject* arrays
	for (int32 i = Array.Num() - 1; i > 0; --i)
	{
		const int32 j = Engine.RandInt(0, i);
		Array.Swap(i, j);
	}
}

float RandomUtility::RandCurveValue(const FRuntimeFloatCurve& Curve)
{
	if (const FRichCurve* RichCurve = Curve.GetRichCurveConst(); RichCurve->Keys.Num() != 0)
	{
		return Engine.RandCurveValue(*RichCurve);
	}
	return 0;
}

float RandomUtility::RandCurveAsset(const UCurveFloat& Curve)
{
	return Engine.RandCurveValue(Curve.FloatCurve);
}

float RandomUtility::RandCurveRange(const FRuntimeFloatCurve& Curve, const float Min, const float Max)
{
	if (const FRichCurve* RichCurve = Curve.GetRichCurveConst())
	{
		return Engine.RandCurveRange(*RichCurve, Min, Max);
	}
	return 0;
}
