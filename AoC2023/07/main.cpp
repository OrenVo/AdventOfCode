#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <cassert>
#include <array>
#include <queue>
#include <stack>

enum Cards {
    c2 = 0, 
    c3,
    c4,
    c5,
    c6,
    c7,
    c8,
    c9,
    cT,
    cJ,
    cQ,
    cK,
    cA
};

inline std::ostream& operator<<(std::ostream & os, Cards card) {
  switch (card) {
  case c2:
      os << "2";
      break;
  case c3:
      os << "3";
      break;
  case c4:
      os << "4";
      break;
  case c5:
      os << "5";
      break;
  case c6:
      os << "6";
      break;
  case c7:
      os << "7";
      break;
  case c8:
      os << "8";
      break;
  case c9:
      os << "9";
      break;
  case cT:
      os << "T";
      break;
  case cJ:
      os << "J";
      break;
  case cQ:
      os << "Q";
      break;
  case cK:
      os << "K";
      break;
  case cA:
      os << "A";
      break;
  }
  return os;
}

enum Cards_part2 {
    cJ_p2 = 0,
    c2_p2, 
    c3_p2,
    c4_p2,
    c5_p2,
    c6_p2,
    c7_p2,
    c8_p2,
    c9_p2,
    cT_p2,
    cQ_p2,
    cK_p2,
    cA_p2
};

inline std::ostream& operator<<(std::ostream & os, Cards_part2 card) {
  switch (card) {
  case c2_p2:
      os << "2";
      break;
  case c3_p2:
      os << "3";
      break;
  case c4_p2:
      os << "4";
      break;
  case c5_p2:
      os << "5";
      break;
  case c6_p2:
      os << "6";
      break;
  case c7_p2:
      os << "7";
      break;
  case c8_p2:
      os << "8";
      break;
  case c9_p2:
      os << "9";
      break;
  case cT_p2:
      os << "T";
      break;
  case cJ_p2:
      os << "J";
      break;
  case cQ_p2:
      os << "Q";
      break;
  case cK_p2:
      os << "K";
      break;
  case cA_p2:
      os << "A";
      break;
  }
  return os;
}

enum Hand_type {
    High_card = 0,
    One_pair,
    Two_pair,
    Three_of_a_kind,
    Full_house,
    Four_of_a_kind,
    Five_of_a_kind,
};

inline std::ostream& operator<<(std::ostream & os, Hand_type type) {
    switch (type)
    {
    case High_card:
        os << "High card";
        break;
    case One_pair:
        os << "One pair";
        break;
    case Two_pair:
        os << "Two pair";
        break;
    case Three_of_a_kind:
        os << "Three of a kind";
        break;
    case Full_house:
        os << "Full house";
        break;
    case Four_of_a_kind:
        os << "Four of a kind";
        break;
    case Five_of_a_kind:
        os << "Five of a kind";
        break;
    }
    return os;
}

struct Hand {
    uint64_t bid;
    std::array<Cards, 5> cards;
    std::array<Cards_part2, 5> cards_part2;
    Hand_type type = High_card;
    Hand_type type_part2 = High_card;
    void type_of_hand() {
        std::array<int, static_cast<int>(Cards::cA) + 1> counts = {};
        for (int i = static_cast<int>(Cards::c2); i <= static_cast<int>(Cards::cA); i++) {
            counts[i] = std::count(cards.begin(), cards.end(), static_cast<Cards>(i));
        }
        bool maybe_full_house = false;
        bool maybe_two_pair = false;
        bool maybe_one_pair = false;
        bool maybe_three_of_a_kind = false;
        for (size_t i = 0; i < counts.size(); i++) {
            if (counts[i] == 5) {
                type = Five_of_a_kind;
                return;
            } else if (counts[i] == 4) {
                type = Four_of_a_kind;
                return;
            } else if (counts[i] == 3) {
                if (maybe_full_house) {
                    type = Full_house;
                    return;
                }
                maybe_full_house = true;
                maybe_three_of_a_kind = true;
            } else if (counts[i] == 2) {
                if (maybe_two_pair) {
                    type = Two_pair;
                    return;
                } else if (maybe_full_house) {
                    type = Full_house;
                    return;
                }
                maybe_full_house = true;
                maybe_one_pair = true;
                maybe_two_pair = true;
            } else if (counts[i] == 1) {
                maybe_full_house = false;                
            }
        }
        if (maybe_three_of_a_kind) {
            type = Three_of_a_kind;
        } else if (maybe_one_pair) {
            type = One_pair;
        } else if (maybe_two_pair) {
            type = Two_pair;
        } else if (maybe_full_house) {
            type = Full_house;
        } else {
            type = High_card;
        }
    }

    void type_part2_hand(){
        type_part2 = type;
        // for (const Cards_part2& c : cards_part2) {
        //     std::cout << c;
        // }
        // std::cout << " " << type_part2 << " ";
        std::array<int, static_cast<int>(Cards_part2::cA_p2) + 1> counts = {};
        for (int i = static_cast<int>(Cards_part2::cJ_p2); i <= static_cast<int>(Cards_part2::cA_p2); i++) {
            counts[i] = std::count(cards_part2.begin(), cards_part2.end(), static_cast<Cards_part2>(i));
        }
        // std::cout << counts[static_cast<int>(Cards_part2::cJ_p2)];
        if (counts[static_cast<int>(Cards_part2::cJ_p2)] == 0 || counts[static_cast<int>(Cards_part2::cJ_p2)] == 5){
            // std::cout << std::endl;
            return;
        }
        if (type == Four_of_a_kind) {
                type_part2 = Five_of_a_kind;
        } else if (type == Full_house){
                type_part2 = Five_of_a_kind;
        } else if (type == Three_of_a_kind){
            if (counts[static_cast<int>(Cards_part2::cJ_p2)] == 1){
                type_part2 = Four_of_a_kind; 
            } else if (counts[static_cast<int>(Cards_part2::cJ_p2)] == 3){
                type_part2 = Four_of_a_kind;
            } 
        } else if (type == Two_pair){
            if (counts[static_cast<int>(Cards_part2::cJ_p2)] == 2){
                type_part2 = Four_of_a_kind;
            } else if (counts[static_cast<int>(Cards_part2::cJ_p2)] == 1){
                type_part2 = Full_house;
            } 
        } else if (type == One_pair){
            type_part2 = Three_of_a_kind;
        } else if (type == High_card){
            type_part2 = One_pair;
        }
        // std::cout << " " << type_part2 << std::endl;
    }

    bool operator<(Hand const& s2) const{
        if (type == s2.type) {
            for(size_t i = 0; i < cards.size(); i++) {
                if (cards[i] != s2.cards[i]) {
                    return cards[i] < s2.cards[i];
                }
            }
            return false;
        } else {
            return type < s2.type;
        }
    }

};

inline bool lt_part2(Hand const& lhs, Hand const& rhs){
        if (lhs.type_part2 == rhs.type_part2) {
            for(size_t i = 0; i < lhs.cards_part2.size(); i++) {
                if (lhs.cards_part2[i] != rhs.cards_part2[i]) {
                    return lhs.cards_part2[i] < rhs.cards_part2[i];
                }
            }
            return false;
        } else {
            return lhs.type_part2 < rhs.type_part2;
        }
}

Hand parse_hand(std::string line) {
    Hand h;
    std::string card = "";
    std::stringstream ss(line);
    ss >> card;
    ss >> h.bid;
    for (int i = 0; i < 5; i++) {
        switch (card[i]) {
            case '2': h.cards[i] = Cards::c2; break;
            case '3': h.cards[i] = Cards::c3; break;
            case '4': h.cards[i] = Cards::c4; break;
            case '5': h.cards[i] = Cards::c5; break;
            case '6': h.cards[i] = Cards::c6; break;
            case '7': h.cards[i] = Cards::c7; break;
            case '8': h.cards[i] = Cards::c8; break;
            case '9': h.cards[i] = Cards::c9; break;
            case 'T': h.cards[i] = Cards::cT; break;
            case 'J': h.cards[i] = Cards::cJ; break;
            case 'Q': h.cards[i] = Cards::cQ; break;
            case 'K': h.cards[i] = Cards::cK; break;
            case 'A': h.cards[i] = Cards::cA; break;
        }
    }
    for (int i = 0; i < 5; i++) {
        switch (card[i]) {
            case '2': h.cards_part2[i] = Cards_part2::c2_p2; break;
            case '3': h.cards_part2[i] = Cards_part2::c3_p2; break;
            case '4': h.cards_part2[i] = Cards_part2::c4_p2; break;
            case '5': h.cards_part2[i] = Cards_part2::c5_p2; break;
            case '6': h.cards_part2[i] = Cards_part2::c6_p2; break;
            case '7': h.cards_part2[i] = Cards_part2::c7_p2; break;
            case '8': h.cards_part2[i] = Cards_part2::c8_p2; break;
            case '9': h.cards_part2[i] = Cards_part2::c9_p2; break;
            case 'T': h.cards_part2[i] = Cards_part2::cT_p2; break;
            case 'J': h.cards_part2[i] = Cards_part2::cJ_p2; break;
            case 'Q': h.cards_part2[i] = Cards_part2::cQ_p2; break;
            case 'K': h.cards_part2[i] = Cards_part2::cK_p2; break;
            case 'A': h.cards_part2[i] = Cards_part2::cA_p2; break;
        }
    }
    h.type_of_hand();
    h.type_part2_hand();
    //std::cout << std::endl;
    return h;
}

int main() {
    std::string line;
    std::vector<Hand> hands = {};
    while (std::getline(std::cin, line)){
        hands.push_back(parse_hand(line));
    }
    std::cout << std::endl;
    std::vector<Hand> hands_part2(hands);
    std::stable_sort(hands.begin(), hands.end());

    size_t sum = 0;
    for (size_t i = 0; i < hands.size(); i++) {
        sum += hands[i].bid * (i + 1);
    }

    // for(const Hand& h : hands){
    //     std::cout << h.bid << " " << h.type << " ";
    //     for (const Cards& c : h.cards) {
    //         std::cout << c;
    //     }
    //     std::cout << std::endl;
    // }
    std::cout << "Part 1: " << sum << std::endl;

    size_t sum_part2 = 0;
    std::stable_sort(hands_part2.begin(), hands_part2.end(), lt_part2);

    for(const Hand& h : hands_part2){
        std::cout << h.bid << " " << h.type_part2 << " ";
        for (const Cards& c : h.cards) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
    
    for (size_t i = 0; i < hands_part2.size(); i++) {
        sum_part2 += hands_part2[i].bid * (i + 1);
    }
    std::cout << "Part 2: " << sum_part2 << std::endl;
    return 0;
}