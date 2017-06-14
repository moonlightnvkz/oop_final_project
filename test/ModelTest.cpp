//
// Created by moonlightnvkz on 07.05.17.
//

#include <gtest/gtest.h>
#include "../include/Model/Card.h"
#include "../include/Model/CardDeck.h"
#include "../include/Model/FoundationStack.h"
#include "../include/Model/TableauStack.h"
#include "../include/Model/Waste.h"
#include "../include/Model/Foundation.h"
#include "../include/Model/Tableau.h"

bool operator==(const Card &a, const Card &b) {
    return a.get_suit() == b.get_suit() &&
           a.get_rank() == b.get_rank();
}

TEST(CardDeckTest, IntegrityTest) {
    CardDeck deck;
    constexpr const unsigned Amount = 52;
    constexpr const unsigned CPS = 13;   // Cards Per Suit
    std::vector<unsigned> cards(Amount, 0);
    for (unsigned i = 0; i < Amount; ++i) {
        std::unique_ptr<Card> card = deck.get_back();
        ++cards[static_cast<unsigned>(card->get_suit()) * CPS + static_cast<unsigned>(card->get_rank())];
        EXPECT_EQ(card->get_side(), Card::eSide::Back);
    }
    for (const auto c : cards) {
        EXPECT_EQ(c, 1);
    }
}

TEST(FoundationTest, StackAddTest) {
    std::unique_ptr<Card> ace_sp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Ace);
    std::unique_ptr<Card> ace_sp_exp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Ace);
    std::unique_ptr<Card> king_sp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::King);
    std::unique_ptr<Card> king_sp_exp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::King);
    std::unique_ptr<Card> two_sp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Two);
    std::unique_ptr<Card> two_sp_exp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Two);
    std::unique_ptr<Card> two_cl = std::make_unique<Card>(Card::eSuit::Clubs, Card::eRank::Two);
    std::unique_ptr<Card> two_cl_exp = std::make_unique<Card>(Card::eSuit::Clubs, Card::eRank::Two);
    FoundationStack stack;
    EXPECT_FALSE(stack.push_back(std::move(two_sp)));
    EXPECT_EQ(stack.size(), 0);
    EXPECT_FALSE(stack.push_back(std::move(king_sp)));
    EXPECT_EQ(stack.size(), 0);
    EXPECT_TRUE(stack.push_back(std::move(ace_sp)));
    EXPECT_EQ(*stack.peek_card(), *ace_sp_exp);
    EXPECT_FALSE(stack.push_back(std::move(two_cl)));
    EXPECT_EQ(*stack.peek_card(), *ace_sp_exp);
    EXPECT_TRUE(stack.push_back(std::move(two_sp)));
    EXPECT_EQ(*stack.peek_card(), *two_sp_exp);
    const std::vector<std::unique_ptr<Card>> &cards = stack.peek_cards();
    ASSERT_EQ(cards.size(), 2);
}

TEST(FoundationTest, CompleteTest) {
    Foundation foundation;
    constexpr const unsigned CPS = 13;   // Cards Per Suit
    constexpr const unsigned Suits = 4;
    for (unsigned i = 0; i < Suits; ++i) {
        FoundationStack &stack = foundation.get_stack(i);
        Card::eSuit suit = static_cast<Card::eSuit>(i);
        for (unsigned j = 0; j < CPS; ++j) {
            Card::eRank rank = static_cast<Card::eRank>(j);
            ASSERT_TRUE(stack.push_back(std::make_unique<Card>(suit, rank)));
        }
    }
    EXPECT_TRUE(foundation.is_complete());
}

TEST(TableauTest, StackAddTest) {
    std::unique_ptr<Card> ace_sp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Ace);
    std::unique_ptr<Card> ace_sp_exp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Ace);
    std::unique_ptr<Card> two_sp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Two);
    std::unique_ptr<Card> two_sp_exp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Two);
    std::unique_ptr<Card> king_sp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::King);
    std::unique_ptr<Card> king_sp_exp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::King);
    std::unique_ptr<Card> queen_sp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Queen);
    std::unique_ptr<Card> queen_sp_exp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Queen);
    std::unique_ptr<Card> queen_he = std::make_unique<Card>(Card::eSuit::Hearts, Card::eRank::Queen);
    std::unique_ptr<Card> queen_he_exp = std::make_unique<Card>(Card::eSuit::Hearts, Card::eRank::Queen);
    TableauStack stack;
    EXPECT_FALSE(stack.push_back(std::move(two_sp)));
    EXPECT_EQ(stack.size(), 0);
    EXPECT_FALSE(stack.push_back(std::move(ace_sp)));
    EXPECT_EQ(stack.size(), 0);
    EXPECT_TRUE(stack.push_back(std::move(king_sp)));
    EXPECT_EQ(*stack.peek_card(), *king_sp_exp);
    EXPECT_FALSE(stack.push_back(std::move(queen_sp)));
    EXPECT_EQ(*stack.peek_card(), *king_sp_exp);
    EXPECT_TRUE(stack.push_back(std::move(queen_he)));
    EXPECT_EQ(*stack.peek_card(), *queen_he_exp);
    const std::vector<std::unique_ptr<Card>> &cards = stack.peek_cards();
    ASSERT_EQ(cards.size(), 2);
}

TEST(TableauTest, InitTest) {
    std::array<TableauStack, 7> stacks;
    std::unique_ptr<Card> cards_exp_init[] = {
            std::make_unique<Card>(Card::eSuit::Hearts, Card::eRank::Nine),
            std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Nine),
            std::make_unique<Card>(Card::eSuit::Clubs, Card::eRank::Nine),
            std::make_unique<Card>(Card::eSuit::Hearts, Card::eRank::Nine),
            std::make_unique<Card>(Card::eSuit::Diamonds, Card::eRank::Nine)
    };
    std::vector<std::unique_ptr<Card>> cards_exp{std::make_move_iterator(std::begin(cards_exp_init)),
                                                 std::make_move_iterator(std::end(cards_exp_init))};
    for (unsigned i = 0; i < 7; ++i) {
        std::unique_ptr<Card> cards_init[] = {
                std::make_unique<Card>(Card::eSuit::Hearts, Card::eRank::Nine),
                std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Nine),
                std::make_unique<Card>(Card::eSuit::Clubs, Card::eRank::Nine),
                std::make_unique<Card>(Card::eSuit::Hearts, Card::eRank::Nine),
                std::make_unique<Card>(Card::eSuit::Diamonds, Card::eRank::Nine)
        };
        std::vector<std::unique_ptr<Card>> cards{std::make_move_iterator(std::begin(cards_init)),
                                                 std::make_move_iterator(std::end(cards_init))};
        TableauStack stack(std::move(cards));
        stacks.at(i) = std::move(stack);
    }
    Tableau tableau(std::move(stacks));
    for (unsigned i = 0; i < 7; ++i) {
        TableauStack &stack = tableau.get_stack(i);
        const std::vector<std::unique_ptr<Card>> &sc = stack.peek_cards();
        ASSERT_EQ(sc.size(), cards_exp.size());
        size_t size = sc.size();
        for (size_t j = 0; j < size; ++j) {
            EXPECT_EQ(*cards_exp[j], *sc[j]);
            EXPECT_EQ(cards_exp[j]->get_side(), Card::eSide::Back);
        }
    }
}

TEST(TableauTest, StackInitTest) {
    std::unique_ptr<Card> stack_init[] = {
            std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Two),
            std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Ace),
            std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Queen),
            std::make_unique<Card>(Card::eSuit::Hearts, Card::eRank::Queen),
            std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::King)
    };
    std::unique_ptr<Card> ace_sp_exp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Ace);
    std::unique_ptr<Card> two_sp_exp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Two);
    std::unique_ptr<Card> king_sp_exp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::King);
    std::unique_ptr<Card> queen_sp_exp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Queen);
    std::unique_ptr<Card> queen_he_exp = std::make_unique<Card>(Card::eSuit::Hearts, Card::eRank::Queen);
    TableauStack stack(std::vector<std::unique_ptr<Card>>(std::make_move_iterator(std::begin(stack_init)),
                                                          std::make_move_iterator(std::end(stack_init))));

    const auto &cards = stack.peek_cards();
    ASSERT_EQ(cards.size(), 5);
    EXPECT_EQ(*stack.peek_card(), *king_sp_exp);
    stack.get_back();
    EXPECT_EQ(*stack.peek_card(), *queen_he_exp);
    stack.get_back();
    EXPECT_EQ(*stack.peek_card(), *queen_sp_exp);
    stack.get_back();
    EXPECT_EQ(*stack.peek_card(), *ace_sp_exp);
    stack.get_back();
    EXPECT_EQ(*stack.peek_card(), *two_sp_exp);
    stack.get_back();
    EXPECT_EQ(stack.size(), 0);
}

TEST(DeckWaste, DeckToWaste) {
    CardDeck deck;
    Waste waste(&deck);

    EXPECT_THROW(deck.move_card_to_waste(), std::logic_error);
    EXPECT_NO_THROW(waste.move_cards_to_deck());
    deck.set_waste(&waste);
    const Card *card = deck.peek_card();
    EXPECT_NO_THROW(deck.move_card_to_waste());
    EXPECT_EQ(*waste.peek_card(), *card);
    waste.move_cards_to_deck();
    EXPECT_EQ(*deck.peek_card(), *card);
}

TEST(TableauTest, ConcatTest) {
    std::unique_ptr<Card> a_init[] = {
            std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::King),
            std::make_unique<Card>(Card::eSuit::Hearts, Card::eRank::Queen)
    };
    std::unique_ptr<Card> b_init[] = {
            std::make_unique<Card>(Card::eSuit::Hearts, Card::eRank::Jack),
            std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Ten)
    };
    std::unique_ptr<Card> c_init[] = {
            std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Jack),
            std::make_unique<Card>(Card::eSuit::Hearts, Card::eRank::Ten)
    };
    std::unique_ptr<Card> king_sp_exp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::King);
    std::unique_ptr<Card> queen_he_exp = std::make_unique<Card>(Card::eSuit::Hearts, Card::eRank::Queen);
    std::unique_ptr<Card> jack_sp_exp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Jack);
    std::unique_ptr<Card> ten_he_exp = std::make_unique<Card>(Card::eSuit::Hearts, Card::eRank::Ten);
    std::unique_ptr<Card> jack_he_exp = std::make_unique<Card>(Card::eSuit::Hearts, Card::eRank::Jack);
    std::unique_ptr<Card> ten_sp_exp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Ten);
    TableauStack a(std::vector<std::unique_ptr<Card>>(std::make_move_iterator(std::begin(a_init)),
                                                      std::make_move_iterator(std::end(a_init))));
    TableauStack b(std::vector<std::unique_ptr<Card>>(std::make_move_iterator(std::begin(b_init)),
                                                      std::make_move_iterator(std::end(b_init))));
    TableauStack c(std::vector<std::unique_ptr<Card>>(std::make_move_iterator(std::begin(c_init)),
                                                      std::make_move_iterator(std::end(c_init))));

    EXPECT_FALSE(a.push_back(std::move(b)));
    EXPECT_EQ(a.peek_cards().size(), 2);
    EXPECT_EQ(*a.peek_cards()[0], *king_sp_exp);
    EXPECT_EQ(*a.peek_cards()[1], *queen_he_exp);

    EXPECT_TRUE(a.push_back(std::move(c)));
    EXPECT_EQ(a.peek_cards().size(), 4);
    EXPECT_EQ(*a.peek_cards()[0], *king_sp_exp);
    EXPECT_EQ(*a.peek_cards()[1], *queen_he_exp);
    EXPECT_EQ(*a.peek_cards()[2], *jack_sp_exp);
    EXPECT_EQ(*a.peek_cards()[3], *ten_he_exp);
}

TEST(TableuTest, PopTaleTest) {
    std::unique_ptr<Card> a_init[] = {std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::King),
                                      std::make_unique<Card>(Card::eSuit::Hearts, Card::eRank::Queen),
                                      std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Jack),
                                      std::make_unique<Card>(Card::eSuit::Hearts, Card::eRank::Ten),
                                      std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Nine),
                                      std::make_unique<Card>(Card::eSuit::Hearts, Card::eRank::Eight)
    };
    std::unique_ptr<Card> king_sp_exp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::King);
    std::unique_ptr<Card> queen_he_exp = std::make_unique<Card>(Card::eSuit::Hearts, Card::eRank::Queen);
    std::unique_ptr<Card> jack_sp_exp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Jack);
    std::unique_ptr<Card> ten_he_exp = std::make_unique<Card>(Card::eSuit::Hearts, Card::eRank::Ten);
    std::unique_ptr<Card> nine_sp_exp = std::make_unique<Card>(Card::eSuit::Spades, Card::eRank::Nine);
    std::unique_ptr<Card> eight_he_exp = std::make_unique<Card>(Card::eSuit::Hearts, Card::eRank::Eight);
    TableauStack a(std::vector<std::unique_ptr<Card>>(std::make_move_iterator(std::begin(a_init)),
                                                      std::make_move_iterator(std::end(a_init))));
    TableauStack tale = a.get_tale(1);
    {
        const std::vector<std::unique_ptr<Card>> &cards = tale.peek_cards();
        ASSERT_EQ(cards.size(), 1);
        EXPECT_EQ(*cards[0], *eight_he_exp);
        a.push_back(std::move(tale));
    }
    tale = a.get_tale(2);
    {
        const std::vector<std::unique_ptr<Card>> &cards = tale.peek_cards();
        ASSERT_EQ(cards.size(), 2);
        EXPECT_EQ(*cards[0], *nine_sp_exp);
        EXPECT_EQ(*cards[1], *eight_he_exp);
        a.push_back(std::move(tale));
    }
    tale = a.get_tale(4);
    {
        const std::vector<std::unique_ptr<Card>> &cards = tale.peek_cards();
        ASSERT_EQ(cards.size(), 4);
        EXPECT_EQ(*cards[0], *jack_sp_exp);
        EXPECT_EQ(*cards[1], *ten_he_exp);
        EXPECT_EQ(*cards[2], *nine_sp_exp);
        EXPECT_EQ(*cards[3], *eight_he_exp);
    }
}