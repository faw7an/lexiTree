#include "pos_dict.h"
#include <unordered_map>

static const std::unordered_map<std::string, POS> DICTIONARY = {
    // 10 determiners
    {"the", POS::DET}, {"a", POS::DET}, {"an", POS::DET}, {"this", POS::DET}, {"that", POS::DET},
    {"these", POS::DET}, {"those", POS::DET}, {"my", POS::DET}, {"your", POS::DET}, {"his", POS::DET},
    
    // 20 nouns
    {"dog", POS::N}, {"cat", POS::N}, {"fox", POS::N}, {"man", POS::N}, {"city", POS::N},
    {"fence", POS::N}, {"tree", POS::N}, {"car", POS::N}, {"house", POS::N}, {"book", POS::N},
    {"water", POS::N}, {"time", POS::N}, {"way", POS::N}, {"day", POS::N}, {"world", POS::N},
    {"life", POS::N}, {"hand", POS::N}, {"part", POS::N}, {"child", POS::N}, {"eye", POS::N},
    
    // 20 verbs
    {"runs", POS::V}, {"jumps", POS::V}, {"eats", POS::V}, {"sees", POS::V}, {"goes", POS::V},
    {"walks", POS::V}, {"talks", POS::V}, {"sleeps", POS::V}, {"makes", POS::V}, {"knows", POS::V},
    {"thinks", POS::V}, {"takes", POS::V}, {"comes", POS::V}, {"wants", POS::V}, {"looks", POS::V},
    {"uses", POS::V}, {"finds", POS::V}, {"gives", POS::V}, {"tells", POS::V}, {"works", POS::V},
    
    // 10 adjectives
    {"quick", POS::ADJ}, {"brown", POS::ADJ}, {"lazy", POS::ADJ}, {"tall", POS::ADJ}, {"happy", POS::ADJ},
    {"good", POS::ADJ}, {"new", POS::ADJ}, {"first", POS::ADJ}, {"last", POS::ADJ}, {"long", POS::ADJ},
    
    // 10 adverbs
    {"quickly", POS::ADV}, {"slowly", POS::ADV}, {"very", POS::ADV}, {"soon", POS::ADV}, {"now", POS::ADV},
    {"always", POS::ADV}, {"never", POS::ADV}, {"often", POS::ADV}, {"well", POS::ADV}, {"hard", POS::ADV},
    
    // 10 prepositions
    {"over", POS::PREP}, {"under", POS::PREP}, {"in", POS::PREP}, {"on", POS::PREP}, {"at", POS::PREP},
    {"by", POS::PREP}, {"to", POS::PREP}, {"with", POS::PREP}, {"from", POS::PREP}, {"into", POS::PREP},
    
    // Pronouns
    {"he", POS::PRON},     {"she", POS::PRON}, {"it", POS::PRON}, {"they", POS::PRON}, {"i", POS::PRON}, 
    {"you", POS::PRON}, {"we", POS::PRON}, {"him", POS::PRON}, {"her", POS::PRON}, {"them", POS::PRON},
    
    // Auxiliaries
    {"has", POS::AUX}, {"have", POS::AUX}, {"had", POS::AUX}, {"can", POS::AUX}, {"could", POS::AUX},
    {"will", POS::AUX}, {"would", POS::AUX}, {"should", POS::AUX}, {"do", POS::AUX}, {"does", POS::AUX},
    {"is", POS::AUX}, {"are", POS::AUX}, {"was", POS::AUX}, {"were", POS::AUX}, {"am", POS::AUX},
    {"loves", POS::V}, {"running", POS::V}, {"sleeps", POS::V},
    
    // Numbers
    {"one", POS::NUM}, {"two", POS::NUM}, {"three", POS::NUM}, {"four", POS::NUM}, {"five", POS::NUM}
};

std::string pos_to_str(POS tag) {
    switch(tag) {
        case POS::DET: return "DET";
        case POS::N: return "N";
        case POS::V: return "V";
        case POS::ADJ: return "ADJ";
        case POS::ADV: return "ADV";
        case POS::PREP: return "PREP";
        case POS::PRON: return "PRON";
        case POS::CONJ: return "CONJ";
        case POS::AUX: return "AUX";
        case POS::NUM: return "NUM";
        case POS::PROPER_N: return "PROPER_N";
        case POS::OP: return "OP";
        case POS::LPAREN: return "LPAREN";
        case POS::RPAREN: return "RPAREN";
        case POS::UNKNOWN: return "UNKNOWN";
        default: return "UNKNOWN";
    }
}

POS lookup_word(const std::string& word) {
    auto it = DICTIONARY.find(word);
    if (it != DICTIONARY.end()) {
        return it->second;
    }
    return POS::UNKNOWN;
}
