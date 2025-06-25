# Mersenne Twister Random - UE5 Plugin

A high-quality random number generation plugin for Unreal Engine 5 that provides superior randomness using the Mersenne Twister algorithm, along with convenient utility functions for generating random Unreal Engine types.

## 🌟 Features

- **High-Quality Random Generation**: Uses Mersenne Twister (mt19937) algorithm for superior randomness compared to built-in UE functions
- **Seeded Generation**: Reproducible random sequences for testing, debugging, and deterministic gameplay
- **Comprehensive UE Type Support**: Generate random vectors, colors, rotators, quaternions, and more
- **Geometric Utilities**: Random points in/on spheres, circles, with proper uniform distribution
- **Array Operations**: Random selection and shuffling with high-quality randomness
- **Curve-Based Generation**: Generate random values using curve assets for custom distributions
- **Performance Optimized**: Efficient C++ implementation with minimal overhead

## ⚠️ Security Disclaimer

**⚠️ IMPORTANT: This plugin is NOT suitable for cryptographic or security applications!**

The Mersenne Twister algorithm, while excellent for games and simulations, is **NOT cryptographically secure**:

- **Predictable**: The internal state can be reconstructed from observing output
- **Not Cryptographically Random**: Does not meet security standards for cryptographic use
- **Deterministic**: Same seed always produces the same sequence

**❌ Do NOT use for:**
- Password generation
- Cryptographic keys
- Security tokens
- Authentication codes
- Any security-critical random values

**✅ Safe for:**
- Game mechanics and procedural generation
- Visual effects and animations
- AI behavior variation
- Simulations and modeling
- Non-security related randomness

For cryptographic applications, use platform-specific secure random generators (e.g., `CryptGenRandom` on Windows, `/dev/urandom` on Unix systems).

## 📦 Installation

1. Download or clone this repository into your project's `Plugins` folder:
   ```
   YourProject/Plugins/MersenneTwisterRandom/
   ```

2. Add the plugin to your project's `.uproject` file:
   ```json
   {
     "Plugins": [
       {
         "Name": "MersenneTwisterRandom",
         "Enabled": true
       }
     ]
   }
   ```

3. Add the module to your project's `Build.cs` file:
   ```cpp
   PublicDependencyModuleNames.AddRange(new string[] { 
       "Core", "CoreUObject", "Engine", "MersenneTwisterRandom" 
   });
   ```

4. Regenerate project files and compile.

## 🚀 Quick Start

### Basic Usage

```cpp
#include "System/RandomEngine.h"
#include "System/RandomUtility.h"

// Create a random engine with automatic seeding
RandomEngine Engine;

// Or use a specific seed for reproducible results
RandomEngine SeededEngine(12345);

// Generate basic random values
int32 RandomInt = Engine.RandInt(1, 100);
float RandomFloat = Engine.RandFloat(0.0f, 1.0f);
bool RandomBool = Engine.RandBool(0.7f); // 70% chance of true

// Use RandomUtility for UE types
RandomUtility Utility;
FVector RandomPosition = Utility.RandVector(-100.0f, 100.0f);
FColor RandomColor = Utility.RandColor();
FRotator RandomRotation = Utility.RandRotator();
```

### Advanced Examples

```cpp
// Generate random points in 3D space
FVector RandomPointInSphere = Utility.RandPointInSphere(50.0f);
FVector RandomPointOnSphere = Utility.RandPointOnSphere(50.0f);

// 2D operations
FVector2D RandomPoint2D = Utility.RandVector2DInCircle(25.0f);
FVector2D RandomDirection2D = Utility.RandVector2DNormalized();

// Array operations
TArray<AActor*> Actors = GetAllActors();
AActor* RandomActor = Utility.RandArrayElementObject(Actors);
Utility.ShuffleArrayObject(Actors);

// Quaternion for smooth rotations
FQuat RandomQuaternion = Utility.RandQuat();

// Curve-based random generation
UCurveFloat* MyCurve = LoadObject<UCurveFloat>(nullptr, TEXT("/Game/Curves/MyCurve"));
float CurveBasedValue = Utility.RandCurveAsset(*MyCurve);
```

## 📚 API Reference

### RandomEngine Class

Core random number generator using Mersenne Twister algorithm.

#### Constructors
- `RandomEngine()` - Auto-seeded with hardware entropy
- `RandomEngine(int32 Seed)` - Seeded for reproducible results

#### Basic Generation
- `int32 RandInt(int32 Min = 0, int32 Max = 1000)` - Random integer
- `float RandFloat(float Min = 0.0f, float Max = 1.0f)` - Random float
- `bool RandBool(float Probability = 0.5f)` - Random boolean

#### Advanced Generation
- `float RandFloatBiased(float Min, float Max, float Bias, int32 Force = 2)` - Biased float
- `bool RandBoolBiased(float Prob = 0.5f, bool BiasTrue = true, int32 Force = 3)` - Biased boolean
- `float RandGaussian(float Mean = 0.0f, float StdDev = 1.0f)` - Gaussian distribution
- `int32 RandWeighted(const TArray<float>& Weights)` - Weighted selection
- `int32 RollDice(int32 NumDice, int32 Sides)` - Dice rolling

#### Static Methods
- `static int32 StaticNewSeed()` - Generate new hardware seed
- `static int32 StaticRandInt(int32 Min, int32 Max)` - One-shot random int
- `static float StaticRandFloat(float Min, float Max)` - One-shot random float
- `static FGuid StaticNewGuid()` - Generate random GUID

### RandomUtility Class

Utility class for generating random Unreal Engine types.

#### Colors
- `FColor RandColor()` - Random RGB color (opaque)
- `FColor RandColorAlpha()` - Random RGBA color (with alpha)

#### 3D Vectors
- `FVector RandVector(float Min, float Max)` - Random vector in range
- `FVector RandVectorNormalized()` - Random unit vector
- `FVector RandPointInSphere(float Radius = 1.0f)` - Random point inside sphere
- `FVector RandPointOnSphere(float Radius = 1.0f)` - Random point on sphere surface

#### 2D Vectors
- `FVector2D RandVector2D(float Min = -1.0f, float Max = 1.0f)` - Random 2D vector
- `FVector2D RandVector2DNormalized()` - Random unit 2D vector
- `FVector2D RandVector2DInCircle(float Radius = 1.0f)` - Random point in circle
- `FVector2D RandVector2DOnCircle(float Radius = 1.0f)` - Random point on circle

#### Rotations
- `FRotator RandRotator()` - Random rotation (Euler angles)
- `FQuat RandQuat()` - Random quaternion (uniform distribution)

#### Array Operations
- `T RandArrayElement<T>(const TArray<T>& Array)` - Random array element
- `void ShuffleArray<T>(TArray<T>& Array)` - Shuffle array in-place
- `UObject* RandArrayElementObject(const TArray<UObject*>& Array)` - Random UObject
- `void ShuffleArrayObject(TArray<UObject*>& Array)` - Shuffle UObject array

#### Curve-Based Generation
- `float RandCurveValue(const FRuntimeFloatCurve& Curve)` - Random value from curve
- `float RandCurveAsset(const UCurveFloat& Curve)` - Random value from curve asset
- `float RandCurveRange(const FRuntimeFloatCurve& Curve, float Min, float Max)` - Curve with range

## 🎨 Blueprint Integration

The plugin provides comprehensive Blueprint support through multiple integration approaches, making high-quality random generation accessible to Blueprint users without C++ knowledge.

### 📋 Integration Methods

#### 1. **TwisterRandomSubsystem** (Recommended)
Global subsystem accessible from anywhere in Blueprints - ideal for most use cases.

**Categories:**
- `Twister Random` - Basic random generation
- `Twister Random|Utility` - Seed management
- `Twister Random|Biased` - Biased random values
- `Twister Random|Gaussian` - Normal distribution
- `Twister Random|Weighted` - Weighted selection
- `Twister Random|Dice` - Dice rolling functions
- `Twister Random|Static` - One-shot generation
- `Twister Random|Unreal` - UE built-in comparison

**Key Functions:**
```cpp
// Basic Generation
Random Float(Min, Max)
Random Integer(Min, Max)
Random Boolean(Probability)

// Utility
Get Root Seed()
Set Seed(Seed)
Reroll Seed()

// Advanced
Random Float Biased(Min, Max, Bias, Force)
Random Gaussian(Mean, StdDev)
Random Weighted(Weights Array)
Roll Dice(NumDice, Sides)

// Static
Generate New Seed()
Generate New GUID()
```

#### 2. **RandomEngineObject** 
UObject wrapper for creating multiple independent random generators.

**Use Cases:**
- Multiple AI agents with separate random streams
- Procedural generation systems that need isolation
- Save/load systems requiring persistent random state

**Key Functions:**
```cpp
// Creation & Setup
Create Random Engine Object(Outer, Seed)
Initialize With Seed(Seed)
Get Root Seed()

// Generation
Get Float(Min, Max)
Get Integer(Min, Max)
Get Bool(Probability)
Get Float Biased(Min, Max, Bias, Force)
Get Float Gaussian(Mean, StdDev)
Get Random Selection(Object Array)
```

#### 3. **RandomEngineBPLibrary**
Blueprint function library for static utility functions.

**Functions:**
- `Random New GUID()` - Generate random GUID
- `Execute Sample Function()` - Testing/demo function

### 🎮 Blueprint Usage Examples

#### Basic Random Generation
```
// Using Subsystem (most common)
1. Get Game Instance Subsystem → Twister Random Subsystem
2. Call "Random Float" with Min=0, Max=100
3. Use result for gameplay logic

// Using Object (for persistent state)
1. Create Random Engine Object with Seed=12345
2. Store reference in variable
3. Call "Get Float" whenever needed
```

#### Advanced Scenarios

**Procedural Level Generation:**
```
// Create seeded generator for level
1. Create Random Engine Object with Level Seed
2. Use Get Float/Integer for positions, scales
3. Use Get Random Selection for asset variants
4. Store object reference for consistent generation
```

**AI Behavior Variation:**
```
// Each AI gets unique random stream
1. For each AI: Create Random Engine Object with unique seed
2. Store as component variable
3. Use Get Float Gaussian for personality traits
4. Use Get Bool for decision making
```

**Weighted Loot System:**
```
// Using subsystem for global loot
1. Create float array: [50.0, 30.0, 15.0, 5.0]
2. Call Random Weighted with weights array
3. Index 0=Common, 1=Uncommon, 2=Rare, 3=Epic
4. Spawn corresponding loot item
```

### 🔧 Blueprint Best Practices

#### **Subsystem vs Object Choice:**
- **Use Subsystem for:** Global random events, UI effects, general gameplay
- **Use Object for:** Persistent state, multiple independent streams, save systems

#### **Seeding Strategies:**
```cpp
// Deterministic (reproducible)
Set Seed(12345) // Fixed seed for testing

// Semi-random (daily variation)
Set Seed(Get Day of Year) // Changes daily

// Fully random
Reroll Seed() // New random seed each time
```

#### **Performance Tips:**
- Cache RandomEngineObject references, don't create new ones each frame
- Use Subsystem for frequent calls (lower overhead)
- Pre-generate arrays of random values for intensive operations

### 🎯 Common Blueprint Patterns

#### **Random Spawning:**
```
1. Get random spawn point: Random Float for X, Y, Z
2. Get random rotation: Random Float for Yaw (-180 to 180)
3. Get random scale: Random Float Gaussian(1.0, 0.1) for variation
4. Spawn actor at calculated transform
```

#### **Conditional Events:**
```
1. Random Boolean with 0.3 probability (30% chance)
2. Branch: True = Spawn rare item, False = Continue
3. Use for random encounters, weather, etc.
```

#### **Value Ranges:**
```
1. Random Float Biased(10, 50, 25, 3) // Biased toward 25
2. Use for AI aggression, spawn rates, etc.
3. Creates more natural-feeling variation
```

### 🔍 Blueprint Categories Reference

| Category | Purpose | Example Functions |
|----------|---------|-------------------|
| `Twister Random` | Core generation | Random Float, Random Integer, Random Boolean |
| `Twister Random\|Utility` | Seed control | Get Root Seed, Set Seed, Reroll Seed |
| `Twister Random\|Biased` | Weighted toward values | Random Float Biased, Random Boolean Biased |
| `Twister Random\|Gaussian` | Bell curve distribution | Random Gaussian, Random Gaussian Clamped |
| `Twister Random\|Weighted` | Array-based selection | Random Weighted |
| `Twister Random\|Dice` | Gaming dice simulation | Roll Dice, Roll Dice Array |
| `Twister Random\|Static` | One-shot generation | Generate New Seed, Generate New GUID |
| `Random Engine` | Object-based generation | Get Float, Get Integer, Get Bool |


## 🎯 Use Cases

### Game Development
```cpp
// Procedural level generation
FVector SpawnPoint = Utility.RandPointInSphere(LevelRadius);
FRotator SpawnRotation = Utility.RandRotator();

// Loot generation with weighted probabilities
TArray<float> LootWeights = {50.0f, 30.0f, 15.0f, 5.0f}; // Common, Uncommon, Rare, Epic
int32 LootTier = Engine.RandWeighted(LootWeights);

// AI behavior variation
float AIPersonality = Engine.RandGaussian(0.5f, 0.2f); // Normal distribution around 0.5
```

### Visual Effects
```cpp
// Particle systems
FVector ParticleVelocity = Utility.RandVectorNormalized() * Speed;
FColor ParticleColor = Utility.RandColorAlpha();

// Random material parameters
float Roughness = Engine.RandFloat(0.1f, 0.9f);
float Metallic = Engine.RandBool(0.3f) ? 1.0f : 0.0f;
```

### Audio Systems
```cpp
// Random audio variations
TArray<UObject*> SoundEffects = GetSoundEffects();
USoundBase* RandomSound = Cast<USoundBase>(Utility.RandArrayElementObject(SoundEffects));

// Pitch/volume variations
float PitchVariation = Engine.RandGaussian(1.0f, 0.1f);
float VolumeVariation = Engine.RandFloat(0.8f, 1.0f);
```

## 🔬 Why Mersenne Twister?

- **Period**: 2^19937-1 (virtually unlimited for games)
- **Quality**: Passes most statistical randomness tests
- **Speed**: Fast generation after initialization
- **Reproducibility**: Same seed = same sequence (crucial for networking/saves)
- **Uniformity**: Better distribution than simple LCG algorithms

## 🆚 Comparison with UE Built-in Random

| Feature | UE Built-in | Mersenne Twister |
|---------|-------------|------------------|
| Quality | Basic LCG | High-quality MT19937 |
| Period | ~2^32 | 2^19937-1 |
| Reproducibility | Platform dependent | Cross-platform consistent |
| Speed | Very fast | Fast |
| Memory | Minimal | ~2.5KB state |
| Thread Safety | Global state | Instance-based |

## 🔧 Advanced Configuration

### Custom Seeding Strategies
```cpp
// Time-based seeding
RandomEngine TimeSeeded(FDateTime::Now().ToUnixTimestamp());

// Player-based seeding
RandomEngine PlayerSeeded(GetPlayerController()->GetUniqueID());

// Level-based seeding
RandomEngine LevelSeeded(GetWorld()->GetName().GetHash());
```

### Performance Considerations
- Use instance-based engines for better thread safety
- Pre-generate random values for real-time critical code
- Consider using static methods for one-off generations

## 🤝 Contributing

Contributions are welcome! Please ensure:
- Code follows UE5 coding standards
- New functions include proper documentation
- Mathematical algorithms are well-commented
- Performance implications are considered

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 🔗 Links

- [Mersenne Twister Wikipedia](https://en.wikipedia.org/wiki/Mersenne_Twister)
- [Unreal Engine Documentation](https://docs.unrealengine.com/)
- [Plugin Source Code](https://github.com/wpatruno/UE5-MersenneTwisterRandom)

## 📝 Changelog

### v1.0.0
- Initial release with RandomEngine and RandomUtility classes
- Support for all major UE5 types
- Geometric utilities for spheres and circles
- Array manipulation functions
- Curve-based random generation
- Comprehensive documentation and examples
