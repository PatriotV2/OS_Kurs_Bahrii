#pragma once

#include <algorithm>
#include <cmath>
#include <cwctype>
#include <functional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <msclr/marshal_cppstd.h>
#using <System.Windows.Forms.dll>

using namespace System;

namespace OSmetod {

	public delegate void OnProgressEvent(float value);

	struct NativeAnalysisResult {
		int positiveScore = 0;
		int negativeScore = 0;
		int tokenCount = 0;
		int matchedTokenCount = 0;
		double sentimentIndex = 0.0;
		std::wstring label;
		std::wstring profileName;
		std::vector<std::wstring> positiveMatches;
		std::vector<std::wstring> negativeMatches;

		static std::wstring JoinMatches(const std::vector<std::wstring>& values) {
			if (values.empty()) {
				return L"немає";
			}

			std::wstringstream stream;
			for (std::size_t i = 0; i < values.size(); ++i) {
				if (i > 0) {
					stream << L", ";
				}
				stream << values[i];
			}
			return stream.str();
		}

		std::wstring ToDisplayString() const {
			std::wstringstream stream;
			stream << L"Профіль аналізу: " << profileName << L"\r\n";
			stream << L"Тональність: " << label << L"\r\n";
			stream << L"Позитивний бал: " << positiveScore << L"\r\n";
			stream << L"Негативний бал: " << negativeScore << L"\r\n";
			stream << L"Кількість токенів: " << tokenCount << L"\r\n";
			stream << L"Збігів у словнику: " << matchedTokenCount << L"\r\n";
			stream << L"Індекс тональності: " << sentimentIndex << L"\r\n\r\n";
			stream << L"Позитивні маркери: " << JoinMatches(positiveMatches) << L"\r\n";
			stream << L"Негативні маркери: " << JoinMatches(negativeMatches) << L"\r\n";
			return stream.str();
		}
	};

	class TextPreprocessorNative {
	public:
		std::wstring Normalize(const std::wstring& text) const {
			std::wstring normalized;
			normalized.reserve(text.size());

			for (wchar_t symbol : text) {
				const wchar_t normalizedSymbol = NormalizeSymbol(symbol);
				if (IsSeparator(normalizedSymbol)) {
					normalized.push_back(L' ');
					continue;
				}

				normalized.push_back(static_cast<wchar_t>(std::towlower(normalizedSymbol)));
			}

			return normalized;
		}

		std::vector<std::wstring> Tokenize(const std::wstring& normalizedText) const {
			std::vector<std::wstring> tokens;
			std::wstringstream stream(normalizedText);
			std::wstring token;

			while (stream >> token) {
				if (!token.empty()) {
					tokens.push_back(token);
				}
			}

			return tokens;
		}

	private:
		static bool IsSeparator(wchar_t symbol) {
			if (symbol == L'\'' || symbol == L'’') {
				return false;
			}

			return std::iswspace(symbol) != 0 || std::iswpunct(symbol) != 0;
		}

		static wchar_t NormalizeSymbol(wchar_t symbol) {
			switch (symbol) {
			case 0x2019: // ’
			case L'`':
				return L'\'';

			case 0x2013:
			case 0x2014:
			case 0x2212:
				return L' ';

			default:
				return symbol;
			}
		}
	};

	class SentimentAnalyzerNative {
	public:
		enum class AnalysisProfile {
			Standard,
			Sensitive,
			Strict
		};

		SentimentAnalyzerNative() :
			positiveLexicon_({
				{L"хорош", 2}, {L"добре", 2}, {L"добр", 2}, {L"чудов", 3}, {L"відмін", 3},
				{L"зручн", 2}, {L"якісн", 2}, {L"швидк", 1}, {L"приємн", 2}, {L"радіс", 2},
				{L"успіш", 2}, {L"сподобал", 3}, {L"корисн", 2}, {L"точн", 2}, {L"стабільн", 2},
				{L"ефективн", 2}, {L"надійн", 2}, {L"excellent", 3}, {L"good", 2}, {L"great", 3},
				{L"happy", 2}, {L"love", 3}, {L"convenient", 2}, {L"useful", 2}, {L"accurate", 2},
				{L"stable", 2}, {L"fast", 1}
				}),
			negativeLexicon_({
				{L"поган", 2}, {L"жахлив", 3}, {L"повільн", 2}, {L"незручн", 2}, {L"помил", 2},
				{L"сумн", 2}, {L"проблем", 2}, {L"гірш", 2}, {L"огидн", 3}, {L"непрац", 3},
				{L"неточн", 2}, {L"нестабільн", 2}, {L"складн", 2}, {L"марн", 2}, {L"bad", 2},
				{L"terrible", 3}, {L"awful", 3}, {L"sad", 2}, {L"hate", 3}, {L"slow", 2},
				{L"inconvenient", 2}, {L"useless", 2}, {L"unstable", 2}, {L"inaccurate", 2}
				}),
			negationWords_({
				{L"не", 1}, {L"ні", 1}, {L"без", 1}, {L"not", 1}, {L"no", 1}
				}) {
		}

		NativeAnalysisResult Analyze(
			const std::wstring& text,
			AnalysisProfile profile,
			const std::function<void(float)>& onProgress = nullptr) const {

			NativeAnalysisResult result;
			result.profileName = ProfileToDisplayName(profile);
			if (onProgress) onProgress(10.0f);

			const std::wstring normalized = preprocessor_.Normalize(text);
			if (onProgress) onProgress(25.0f);

			const std::vector<std::wstring> tokens = preprocessor_.Tokenize(normalized);
			result.tokenCount = static_cast<int>(tokens.size());
			bool invertNextToken = false;

			for (std::size_t i = 0; i < tokens.size(); ++i) {
				const std::wstring& token = tokens[i];

				if (negationWords_.find(token) != negationWords_.end()) {
					invertNextToken = true;
					continue;
				}

				int positiveWeight = MatchLexiconWeight(token, positiveLexicon_);
				int negativeWeight = MatchLexiconWeight(token, negativeLexicon_);

				if (positiveWeight == 0 && negativeWeight == 0) {
					const std::wstring strippedToken = StripNegationPrefix(token);
					if (!strippedToken.empty()) {
						const int strippedPositiveWeight = MatchLexiconWeight(strippedToken, positiveLexicon_);
						const int strippedNegativeWeight = MatchLexiconWeight(strippedToken, negativeLexicon_);
						negativeWeight += strippedPositiveWeight;
						positiveWeight += strippedNegativeWeight;
					}
				}

				if (invertNextToken) {
					std::swap(positiveWeight, negativeWeight);
					invertNextToken = false;
				}

				if (positiveWeight > 0) {
					result.positiveScore += positiveWeight;
					result.positiveMatches.push_back(token);
				}

				if (negativeWeight > 0) {
					result.negativeScore += negativeWeight;
					result.negativeMatches.push_back(token);
				}

				if (onProgress && !tokens.empty()) {
					const float progress = 25.0f + 55.0f * static_cast<float>(i + 1) / static_cast<float>(tokens.size());
					onProgress(progress);
				}
			}

			result.matchedTokenCount = static_cast<int>(result.positiveMatches.size() + result.negativeMatches.size());
			result.sentimentIndex = CalculateIndex(result.positiveScore, result.negativeScore);
			result.label = ResolveLabel(result.sentimentIndex, profile);

			if (onProgress) onProgress(100.0f);
			return result;
		}

		static std::wstring ProfileToDisplayName(AnalysisProfile profile) {
			switch (profile) {
			case AnalysisProfile::Sensitive:
				return L"Чутливий";
			case AnalysisProfile::Strict:
				return L"Строгий";
			case AnalysisProfile::Standard:
			default:
				return L"Стандартний";
			}
		}

	private:
		TextPreprocessorNative preprocessor_;
		std::unordered_map<std::wstring, int> positiveLexicon_;
		std::unordered_map<std::wstring, int> negativeLexicon_;
		std::unordered_map<std::wstring, int> negationWords_;

		static double CalculateIndex(int positiveScore, int negativeScore) {
			const int total = positiveScore + negativeScore;
			if (total == 0) {
				return 0.0;
			}

			const double rawIndex = static_cast<double>(positiveScore - negativeScore) / static_cast<double>(total);
			return std::round(rawIndex * 100.0) / 100.0;
		}

		static double ResolveThreshold(AnalysisProfile profile) {
			switch (profile) {
			case AnalysisProfile::Sensitive:
				return 0.10;
			case AnalysisProfile::Strict:
				return 0.30;
			case AnalysisProfile::Standard:
			default:
				return 0.18;
			}
		}

		static std::wstring ResolveLabel(double sentimentIndex, AnalysisProfile profile) {
			const double threshold = ResolveThreshold(profile);
			if (sentimentIndex >= threshold) {
				return L"Позитивна";
			}
			if (sentimentIndex <= -threshold) {
				return L"Негативна";
			}
			return L"Нейтральна";
		}

		int MatchLexiconWeight(const std::wstring& token, const std::unordered_map<std::wstring, int>& lexicon) const {
			int matchedWeight = 0;
			std::size_t bestMatchLength = 0;

			for (const auto& pair : lexicon) {
				const std::wstring& root = pair.first;
				const int weight = pair.second;

				if (token == root || token.rfind(root, 0) == 0) {
					if (root.size() > bestMatchLength) {
						bestMatchLength = root.size();
						matchedWeight = weight;
					}
				}
			}

			return matchedWeight;
		}

		static std::wstring StripNegationPrefix(const std::wstring& token) {
			if (token.size() > 3 && token.rfind(L"не", 0) == 0) {
				return token.substr(2);
			}
			if (token.size() > 4 && token.rfind(L"not", 0) == 0) {
				return token.substr(3);
			}
			return L"";
		}
	};

	public ref class ManagedAnalysisResult
	{
	public:
		property int PositiveScore;
		property int NegativeScore;
		property int TokenCount;
		property int MatchedTokenCount;
		property double SentimentIndex;
		property String^ Label;
		property String^ ProfileName;
		property String^ PositiveMatches;
		property String^ NegativeMatches;
		property String^ DisplayText;
	};

	public ref class SentimentService
	{
	private:
		SentimentAnalyzerNative* analyzer_;

	public:
		OnProgressEvent^ OnProgress;

		SentimentService() {
			analyzer_ = new SentimentAnalyzerNative();
			OnProgress = nullptr;
		}

		~SentimentService() {
			this->!SentimentService();
		}

		!SentimentService() {
			if (analyzer_ != nullptr) {
				delete analyzer_;
				analyzer_ = nullptr;
			}
		}

		ManagedAnalysisResult^ Analyze(String^ text, String^ profileName) {

			String^ safeText = text == nullptr ? String::Empty : text;
			std::wstring nativeText = msclr::interop::marshal_as<std::wstring>(safeText);

			const SentimentAnalyzerNative::AnalysisProfile profile = ParseProfile(profileName);

			// без callback
			NativeAnalysisResult nativeResult = analyzer_->Analyze(nativeText, profile, nullptr);

			if (OnProgress != nullptr) {
				OnProgress(100.0f);
			}

			ManagedAnalysisResult^ managedResult = gcnew ManagedAnalysisResult();
			managedResult->PositiveScore = nativeResult.positiveScore;
			managedResult->NegativeScore = nativeResult.negativeScore;
			managedResult->TokenCount = nativeResult.tokenCount;
			managedResult->MatchedTokenCount = nativeResult.matchedTokenCount;
			managedResult->SentimentIndex = nativeResult.sentimentIndex;
			managedResult->Label = gcnew String(nativeResult.label.c_str());
			managedResult->ProfileName = gcnew String(nativeResult.profileName.c_str());
			managedResult->PositiveMatches = gcnew String(NativeAnalysisResult::JoinMatches(nativeResult.positiveMatches).c_str());
			managedResult->NegativeMatches = gcnew String(NativeAnalysisResult::JoinMatches(nativeResult.negativeMatches).c_str());
			managedResult->DisplayText = gcnew String(nativeResult.ToDisplayString().c_str());

			return managedResult;
		}

	private:
		static void OnProgressThunk(SentimentService^ self, float value) {
			if (self->OnProgress != nullptr) {
				self->OnProgress(value);
			}
		}

	private:
		static SentimentAnalyzerNative::AnalysisProfile ParseProfile(String^ profileName) {
			if (String::IsNullOrWhiteSpace(profileName)) {
				return SentimentAnalyzerNative::AnalysisProfile::Standard;
			}

			if (profileName->Equals(L"Чутливий")) {
				return SentimentAnalyzerNative::AnalysisProfile::Sensitive;
			}

			if (profileName->Equals(L"Строгий")) {
				return SentimentAnalyzerNative::AnalysisProfile::Strict;
			}

			return SentimentAnalyzerNative::AnalysisProfile::Standard;
		}
	};
}
