// Fill out your copyright notice in the Description page of Project Settings.


#include "System/RandomString.h"


/**
 * Default constructor - Initializes with a random seed
 */
RandomString::RandomString() : Engine(RandomEngine::StaticNewSeed())
{
}

/**
 * Constructor - Initializes the random engine with a specific seed
 * @param InSeed - The seed value for reproducible random generation
 */
RandomString::RandomString(int32 InSeed) : Engine(InSeed)
{
}

/**
 * Destructor
 */
RandomString::~RandomString()
{
}

/**
 * Gets the current seed used by the random engine
 * @return The seed value
 */
int32 RandomString::GetSeed() const
{
	return Engine.GetRootSeed();
}

/* CHARACTER GENERATION */

/**
 * Generates a random character from a specified character set
 * @param CharType - Type of characters to generate
 * @param CustomChars - Custom character set when using ECharacterType::Custom
 * @return Random character from the specified set
 */
TCHAR RandomString::RandChar(ECharacterType CharType, const FString& CustomChars)
{
	FString CharacterSet = GetCharacterSet(CharType);
	
	// Use custom characters if specified
	if (CharType == ECharacterType::Custom)
	{
		CharacterSet = CustomChars;
	}
	
	// Return space if character set is empty
	if (CharacterSet.IsEmpty())
	{
		return TEXT(' ');
	}
	
	// Generate random index and return character
	const int32 RandomIndex = Engine.RandInt(0, CharacterSet.Len() - 1);
	return CharacterSet[RandomIndex];
}

/**
 * Generates a random uppercase letter (A-Z)
 * @return Random uppercase letter
 */
TCHAR RandomString::RandUppercase()
{
	return RandChar(ECharacterType::Uppercase);
}

/**
 * Generates a random lowercase letter (a-z)
 * @return Random lowercase letter
 */
TCHAR RandomString::RandLowercase()
{
	return RandChar(ECharacterType::Lowercase);
}

/**
 * Generates a random digit (0-9)
 * @return Random digit character
 */
TCHAR RandomString::RandDigit()
{
	return RandChar(ECharacterType::Numeric);
}

/**
 * Generates a random alphabetic character (A-Z, a-z)
 * @return Random alphabetic character
 */
TCHAR RandomString::RandAlpha()
{
	return RandChar(ECharacterType::Alpha);
}

/**
 * Generates a random alphanumeric character (A-Z, a-z, 0-9)
 * @return Random alphanumeric character
 */
TCHAR RandomString::RandAlphaNumeric()
{
	return RandChar(ECharacterType::AlphaNumeric);
}

/**
 * Generates a random symbol character
 * @return Random symbol character
 */
TCHAR RandomString::RandSymbol()
{
	return RandChar(ECharacterType::Symbols);
}

/* STRING GENERATION */

/**
 * Generates a random string with specified length and character type
 * @param Length - Length of the string to generate
 * @param CharType - Type of characters to use
 * @param CustomChars - Custom character set when using ECharacterType::Custom
 * @return Random string of specified length
 */
FString RandomString::RandString(int32 Length, ECharacterType CharType, const FString& CustomChars)
{
	if (Length <= 0)
	{
		return FString();
	}

	FString Result;
	Result.Reserve(Length);

	for (int32 i = 0; i < Length; ++i)
	{
		Result += RandChar(CharType, CustomChars);
	}

	return Result;
}

/**
 * Generates a random password with specified criteria
 * @param Length - Length of the password
 * @param IncludeUppercase - Include uppercase letters
 * @param IncludeLowercase - Include lowercase letters
 * @param IncludeNumbers - Include numbers
 * @param IncludeSymbols - Include symbols
 * @return Random password string
 */
FString RandomString::RandPassword(int32 Length, bool IncludeUppercase, bool IncludeLowercase, bool IncludeNumbers, bool IncludeSymbols)
{
	if (Length <= 0)
	{
		return FString();
	}

	// Build character set based on criteria
	FString CharacterSet;
	if (IncludeUppercase) CharacterSet += TEXT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	if (IncludeLowercase) CharacterSet += TEXT("abcdefghijklmnopqrstuvwxyz");
	if (IncludeNumbers) CharacterSet += TEXT("0123456789");
	if (IncludeSymbols) CharacterSet += TEXT("!@#$%^&*()_+-=[]{}|;:,.<>?");

	// Fallback to alphanumeric if no criteria selected
	if (CharacterSet.IsEmpty())
	{
		CharacterSet = TEXT("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
	}

	return RandString(Length, ECharacterType::Custom, CharacterSet);
}

/**
 * Generates a random identifier (starts with letter, contains alphanumeric)
 * @param Length - Length of the identifier
 * @param UseUppercase - Whether to use uppercase letters
 * @return Random identifier string
 */
FString RandomString::RandIdentifier(int32 Length, bool UseUppercase)
{
	if (Length <= 0)
	{
		return FString();
	}

	FString Result;
	Result.Reserve(Length);

	// First character must be a letter
	if (UseUppercase)
	{
		Result += RandUppercase();
	}
	else
	{
		Result += RandLowercase();
	}

	// Remaining characters can be alphanumeric
	const ECharacterType CharType = UseUppercase ? ECharacterType::Custom : ECharacterType::AlphaNumeric;
	const FString CustomChars = UseUppercase ? TEXT("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") : TEXT("");

	for (int32 i = 1; i < Length; ++i)
	{
		Result += RandChar(CharType, CustomChars);
	}

	return Result;
}

/**
 * Generates a random hex string
 * @param Length - Length of the hex string
 * @param IncludePrefix - Whether to include "0x" prefix
 * @return Random hex string
 */
FString RandomString::RandHexString(int32 Length, bool IncludePrefix)
{
	if (Length <= 0)
	{
		return IncludePrefix ? TEXT("0x") : FString();
	}

	FString Result;
	if (IncludePrefix)
	{
		Result = TEXT("0x");
	}

	const FString HexChars = TEXT("0123456789ABCDEF");
	for (int32 i = 0; i < Length; ++i)
	{
		Result += RandChar(ECharacterType::Custom, HexChars);
	}

	return Result;
}

/**
 * Generates a random name-like string
 * @param MinLength - Minimum length of the name
 * @param MaxLength - Maximum length of the name
 * @return Random name string (first letter uppercase, rest lowercase)
 */
FString RandomString::RandName(int32 MinLength, int32 MaxLength)
{
	if (MinLength <= 0 || MaxLength < MinLength)
	{
		return FString();
	}

	const int32 Length = Engine.RandInt(MinLength, MaxLength);
	FString Result;
	Result.Reserve(Length);

	// First character is uppercase
	Result += RandUppercase();

	// Remaining characters are lowercase
	for (int32 i = 1; i < Length; ++i)
	{
		Result += RandLowercase();
	}

	return Result;
}

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
FString RandomString::RandStringFromPattern(const FString& Pattern, const FString& CustomChars)
{
	FString Result;
	Result.Reserve(Pattern.Len());

	for (int32 i = 0; i < Pattern.Len(); ++i)
	{
		const TCHAR PatternChar = Pattern[i];

		switch (PatternChar)
		{
		case TEXT('A'):
			Result += RandUppercase();
			break;
		case TEXT('a'):
			Result += RandLowercase();
			break;
		case TEXT('9'):
			Result += RandDigit();
			break;
		case TEXT('X'):
			Result += RandAlphaNumeric();
			break;
		case TEXT('?'):
			Result += RandChar(ECharacterType::All);
			break;
		case TEXT('*'):
			Result += RandChar(ECharacterType::Custom, CustomChars);
			break;
		default:
			// Literal character
			Result += PatternChar;
			break;
		}
	}

	return Result;
}

/* UTILITY METHODS */

/**
 * Shuffles the characters in a string
 * @param InputString - String to shuffle
 * @return Shuffled string
 */
FString RandomString::ShuffleString(const FString& InputString)
{
	if (InputString.IsEmpty())
	{
		return FString();
	}

	// Convert to array for shuffling
	TArray<TCHAR> CharArray;
	for (int32 i = 0; i < InputString.Len(); ++i)
	{
		CharArray.Add(InputString[i]);
	}

	// Fisher-Yates shuffle
	for (int32 i = CharArray.Num() - 1; i > 0; --i)
	{
		const int32 j = Engine.RandInt(0, i);
		CharArray.Swap(i, j);
	}

	// Convert back to string
	FString Result;
	Result.Reserve(CharArray.Num());
	for (const TCHAR& Char : CharArray)
	{
		Result += Char;
	}

	return Result;
}

/**
 * Generates a random substring from the input string
 * @param InputString - Source string
 * @param MinLength - Minimum length of substring
 * @param MaxLength - Maximum length of substring
 * @return Random substring
 */
FString RandomString::RandSubstring(const FString& InputString, int32 MinLength, int32 MaxLength)
{
	if (InputString.IsEmpty() || MinLength <= 0)
	{
		return FString();
	}

	// Default MaxLength to string length
	if (MaxLength <= 0 || MaxLength > InputString.Len())
	{
		MaxLength = InputString.Len();
	}

	// Clamp MinLength
	MinLength = FMath::Min(MinLength, InputString.Len());
	MaxLength = FMath::Max(MinLength, MaxLength);

	const int32 SubstringLength = Engine.RandInt(MinLength, FMath::Min(MaxLength, InputString.Len()));
	const int32 MaxStartIndex = InputString.Len() - SubstringLength;
	const int32 StartIndex = Engine.RandInt(0, FMath::Max(0, MaxStartIndex));

	return InputString.Mid(StartIndex, SubstringLength);
}

/**
 * Capitalizes random characters in a string
 * @param InputString - Input string
 * @param Probability - Probability of capitalizing each character (0.0-1.0)
 * @return String with randomly capitalized characters
 */
FString RandomString::RandomCapitalization(const FString& InputString, float Probability)
{
	FString Result;
	Result.Reserve(InputString.Len());

	for (int32 i = 0; i < InputString.Len(); ++i)
	{
		TCHAR Char = InputString[i];

		// Only apply to alphabetic characters
		if (FChar::IsAlpha(Char))
		{
			if (Engine.RandBool(Probability))
			{
				Char = FChar::ToUpper(Char);
			}
			else
			{
				Char = FChar::ToLower(Char);
			}
		}

		Result += Char;
	}

	return Result;
}

/* STATIC UTILITY METHODS */

/**
 * Gets a predefined character set by enum type
 * @param CharType - Character type enum
 * @return Character set string
 */
FString RandomString::GetCharacterSet(ECharacterType CharType)
{
	const FString UppercaseChars = TEXT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	const FString LowercaseChars = TEXT("abcdefghijklmnopqrstuvwxyz");
	const FString NumericChars = TEXT("0123456789");
	const FString SymbolChars = TEXT("!@#$%^&*()_+-=[]{}|;:,.<>?");
	const FString AlphaChars = UppercaseChars + LowercaseChars;
	const FString AlphaNumericChars = AlphaChars + NumericChars;
	const FString AllChars = AlphaNumericChars + SymbolChars;

	if (CharType == ECharacterType::Alpha)
	{
		return AlphaChars;
	}
	else if (CharType == ECharacterType::Numeric)
	{
		return NumericChars;
	}
	else if (CharType == ECharacterType::AlphaNumeric)
	{
		return AlphaNumericChars;
	}
	else if (CharType == ECharacterType::Uppercase)
	{
		return UppercaseChars;
	}
	else if (CharType == ECharacterType::Lowercase)
	{
		return LowercaseChars;
	}
	else if (CharType == ECharacterType::Symbols)
	{
		return SymbolChars;
	}
	else // Default to "All"
	{
		return AllChars;
	}
}

/**
 * Validates if a character belongs to a specific character set
 * @param Character - Character to validate
 * @param CharType - Character type to check against
 * @return True if character belongs to the set
 */
bool RandomString::IsCharInSet(TCHAR Character, ECharacterType CharType)
{
	const FString CharacterSet = GetCharacterSet(CharType);
	return CharacterSet.Contains(FString::Chr(Character));
}

/**
 * Converts string character type name to enum (for backward compatibility)
 * @param CharTypeName - String name of character type
 * @return Corresponding enum value
 */
ECharacterType RandomString::StringToCharacterType(const FString& CharTypeName)
{
	if (CharTypeName.Equals(TEXT("Alpha"), ESearchCase::IgnoreCase))
	{
		return ECharacterType::Alpha;
	}
	else if (CharTypeName.Equals(TEXT("Numeric"), ESearchCase::IgnoreCase))
	{
		return ECharacterType::Numeric;
	}
	else if (CharTypeName.Equals(TEXT("AlphaNumeric"), ESearchCase::IgnoreCase))
	{
		return ECharacterType::AlphaNumeric;
	}
	else if (CharTypeName.Equals(TEXT("Uppercase"), ESearchCase::IgnoreCase))
	{
		return ECharacterType::Uppercase;
	}
	else if (CharTypeName.Equals(TEXT("Lowercase"), ESearchCase::IgnoreCase))
	{
		return ECharacterType::Lowercase;
	}
	else if (CharTypeName.Equals(TEXT("Symbols"), ESearchCase::IgnoreCase))
	{
		return ECharacterType::Symbols;
	}
	else if (CharTypeName.Equals(TEXT("Custom"), ESearchCase::IgnoreCase))
	{
		return ECharacterType::Custom;
	}
	else // Default to "All"
	{
		return ECharacterType::All;
	}
} 