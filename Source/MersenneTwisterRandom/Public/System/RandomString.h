// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/RandomEngine.h"

/**
 * Enum for specifying character set types
 */
UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	All           UMETA(DisplayName = "All Characters"),
	Alpha         UMETA(DisplayName = "Alphabetic (A-Z, a-z)"),
	Numeric       UMETA(DisplayName = "Numeric (0-9)"),
	AlphaNumeric  UMETA(DisplayName = "Alphanumeric (A-Z, a-z, 0-9)"),
	Uppercase     UMETA(DisplayName = "Uppercase (A-Z)"),
	Lowercase     UMETA(DisplayName = "Lowercase (a-z)"),
	Symbols       UMETA(DisplayName = "Symbols (!@#$%...)"),
	Custom        UMETA(DisplayName = "Custom Character Set")
};

/**
 * RandomString - Specialized character and string generation using RandomEngine
 * 
 * This class provides comprehensive character and string generation capabilities
 * using the high-quality RandomEngine for consistent, seeded randomization.
 * 
 * Features:
 * - Character generation from predefined sets
 * - String generation with various patterns
 * - Password and identifier generation
 * - Name generation utilities
 * - Custom character set support
 */
class MERSENNETWISTERRANDOM_API RandomString
{
private:
	/** The RandomEngine instance used for all random generation */
	RandomEngine Engine;

public:
	/**
	 * Default constructor - Initializes with a random seed
	 */
	RandomString();

	/**
	 * Constructor - Initializes the random engine with a specific seed
	 * @param InSeed - The seed value for reproducible random generation
	 */
	RandomString(int32 InSeed);
	
	/**
	 * Destructor
	 */
	~RandomString();

	/**
	 * Gets the current seed used by the random engine
	 * @return The seed value
	 */
	int32 GetSeed() const;

	/* CHARACTER GENERATION */

	/**
	 * Generates a random character from a specified character set
	 * @param CharType - Type of characters to generate
	 * @param CustomChars - Custom character set when using ECharacterType::Custom
	 * @return Random character from the specified set
	 */
	TCHAR RandChar(ECharacterType CharType = ECharacterType::All, const FString& CustomChars = TEXT(""));

	/**
	 * Generates a random uppercase letter (A-Z)
	 * @return Random uppercase letter
	 */
	TCHAR RandUppercase();

	/**
	 * Generates a random lowercase letter (a-z)
	 * @return Random lowercase letter
	 */
	TCHAR RandLowercase();

	/**
	 * Generates a random digit (0-9)
	 * @return Random digit character
	 */
	TCHAR RandDigit();

	/**
	 * Generates a random alphabetic character (A-Z, a-z)
	 * @return Random alphabetic character
	 */
	TCHAR RandAlpha();

	/**
	 * Generates a random alphanumeric character (A-Z, a-z, 0-9)
	 * @return Random alphanumeric character
	 */
	TCHAR RandAlphaNumeric();

	/**
	 * Generates a random symbol character
	 * @return Random symbol character
	 */
	TCHAR RandSymbol();

	/* STRING GENERATION */

	/**
	 * Generates a random string with specified length and character type
	 * @param Length - Length of the string to generate
	 * @param CharType - Type of characters to use
	 * @param CustomChars - Custom character set when using ECharacterType::Custom
	 * @return Random string of specified length
	 */
	FString RandString(int32 Length, ECharacterType CharType = ECharacterType::AlphaNumeric, const FString& CustomChars = TEXT(""));

	/**
	 * Generates a random password with specified criteria
	 * @param Length - Length of the password
	 * @param IncludeUppercase - Include uppercase letters
	 * @param IncludeLowercase - Include lowercase letters
	 * @param IncludeNumbers - Include numbers
	 * @param IncludeSymbols - Include symbols
	 * @return Random password string
	 */
	FString RandPassword(int32 Length = 12, bool IncludeUppercase = true, bool IncludeLowercase = true, bool IncludeNumbers = true, bool IncludeSymbols = false);

	/**
	 * Generates a random identifier (starts with letter, contains alphanumeric)
	 * @param Length - Length of the identifier
	 * @param UseUppercase - Whether to use uppercase letters
	 * @return Random identifier string
	 */
	FString RandIdentifier(int32 Length = 8, bool UseUppercase = false);

	/**
	 * Generates a random hex string
	 * @param Length - Length of the hex string
	 * @param IncludePrefix - Whether to include "0x" prefix
	 * @return Random hex string
	 */
	FString RandHexString(int32 Length = 8, bool IncludePrefix = false);

	/**
	 * Generates a random name-like string
	 * @param MinLength - Minimum length of the name
	 * @param MaxLength - Maximum length of the name
	 * @return Random name string (first letter uppercase, rest lowercase)
	 */
	FString RandName(int32 MinLength = 4, int32 MaxLength = 10);

	/**
	 * Generates a random string from a pattern
	 * Pattern characters:
	 * - 'A' = Uppercase letter
	 * - 'a' = Lowercase letter
	 * - '9' = Digit
	 * - 'X' = Alphanumeric
	 * - '?' = Any character
	 * - '*' = Random character from custom set
	 * @param Pattern - Pattern string defining the format
	 * @param CustomChars - Custom characters for '*' pattern character
	 * @return String matching the specified pattern
	 */
	FString RandStringFromPattern(const FString& Pattern, const FString& CustomChars = TEXT(""));

	/* UTILITY METHODS */

	/**
	 * Shuffles the characters in a string
	 * @param InputString - String to shuffle
	 * @return Shuffled string
	 */
	FString ShuffleString(const FString& InputString);

	/**
	 * Generates a random substring from the input string
	 * @param InputString - Source string
	 * @param MinLength - Minimum length of substring
	 * @param MaxLength - Maximum length of substring
	 * @return Random substring
	 */
	FString RandSubstring(const FString& InputString, int32 MinLength = 1, int32 MaxLength = -1);

	/**
	 * Capitalizes random characters in a string
	 * @param InputString - Input string
	 * @param Probability - Probability of capitalizing each character (0.0-1.0)
	 * @return String with randomly capitalized characters
	 */
	FString RandomCapitalization(const FString& InputString, float Probability = 0.5f);

	/* STATIC UTILITY METHODS */

	/**
	 * Gets a predefined character set by enum type
	 * @param CharType - Character type enum
	 * @return Character set string
	 */
	static FString GetCharacterSet(ECharacterType CharType);

	/**
	 * Validates if a character belongs to a specific character set
	 * @param Character - Character to validate
	 * @param CharType - Character type to check against
	 * @return True if character belongs to the set
	 */
	static bool IsCharInSet(TCHAR Character, ECharacterType CharType);

	/**
	 * Converts string character type name to enum (for backward compatibility)
	 * @param CharTypeName - String name of character type
	 * @return Corresponding enum value
	 */
	static ECharacterType StringToCharacterType(const FString& CharTypeName);
}; 