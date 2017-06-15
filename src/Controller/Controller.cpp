//
// Created by moonlightnvkz on 26.05.17.
//

#include <include/Settings.h>
#include "include/Controller/Controller.h"
#include "include/View/StackLayoutView.h"
#include "include/View/CardContainerView.h"
#include "include/View/GameBoardView.h"
#include "include/View/TableauStackView.h"
#include "include/Model/Tableau.h"
#include "include/Model/Foundation.h"
#include "include/Model/Waste.h"
#include "include/Model/CardDeck.h"
#include "include/Model/GameBoard.h"

Controller::Controller(GameBoard *model, GameBoardView *view)
        : model(model), view(view), origin(Origin::Tableau), origin_descr{0, 0} {
    sync_view_with_model();
}

void Controller::turn_deck() {
    if (model->deck->size() == 0) {
        model->waste->move_cards_to_deck();
    } else {
        model->deck->move_card_to_waste();
    }
    view->deck->update(*model->deck);
    view->waste->update(*model->waste);
}

void Controller::card_from_waste_is_taken() {
    origin = Origin::Waste;
}

void Controller::card_from_foundation_is_taken(const unsigned i) {
    origin = Origin::Foundation;
    origin_descr.first = i;
}

void Controller::tableau_stack_tale_is_taken(const unsigned i, const size_t amount) {
    origin = Origin::Tableau;
    origin_descr.first = i;
    origin_descr.second = amount;
}

bool Controller::put_to_tableau_stack(const unsigned j) {
    bool res = false;
    switch (origin) {
        case Origin::Waste: {
            const Card *card = model->waste->peek_card();
            TableauStack &to = model->tableau->get_stack(j);
            if (to.is_suitable(card)) {
                res = to.push_back(model->waste->get_back());
                view->waste->update(*model->waste);
                view->tableau->update(to, j);
            }
            break;
        }
        case Origin::Tableau: {
            if (j == origin_descr.first) {
                return true;
            }
            TableauStack &from = model->tableau->get_stack(origin_descr.first);
            const std::vector<const Card *> tale = from.peek_tale(origin_descr.second);
            TableauStack &to = model->tableau->get_stack(j);
            if (to.is_suitable(tale)) {
                res = to.push_back(from.get_tale(origin_descr.second));
                view->tableau->update(from, origin_descr.first);
                view->tableau->update(to, j);
            }
            break;
        }
        case Origin::Foundation: {
            FoundationStack &from = model->foundation->get_stack(origin_descr.first);
            const Card *card = from.peek_card();
            TableauStack &to = model->tableau->get_stack(j);
            if (to.is_suitable(card)) {
                res = to.push_back(from.get_back());
                view->foundation->update(from, origin_descr.first);
                view->tableau->update(to, j);
            }
            break;
        }
        default:;
    }

    release_back();
    return res;
}

bool Controller::put_to_foundation_stack(const unsigned j) {
    bool res = false;
    switch (origin) {
        case Origin::Waste: {
            FoundationStack &to = model->foundation->get_stack(j);
            const Card *card = model->waste->peek_card();
            if (to.is_suitable(card)) {
                res = to.push_back(model->waste->get_back());
                view->waste->update(*model->waste);
                view->foundation->update(to, j);
            }
            break;
        }
        case Origin::Tableau: {
            if (origin_descr.second == 1) {
                FoundationStack &to = model->foundation->get_stack(j);
                TableauStack &from = model->tableau->get_stack(origin_descr.first);
                const Card *card = from.peek_card();
                if (to.is_suitable(card)) {
                    res = to.push_back(from.get_back());
                    view->tableau->update(from, origin_descr.first);
                    view->foundation->update(to, j);
                }
            }
            break;
        }
        case Origin::Foundation:    // No need to support this because of rules
        default:;
    }
    release_back();
    if (model->foundation->is_complete()) {
        if (view->show_congratulations_window()) {
            restart_game();
        }
    }
    return res;
}

void Controller::release_back() {
    origin = Origin::None;
}

void Controller::sync_view_with_model() {
    std::vector<std::reference_wrapper<const CardContainer>> stacks;
    for (const auto &s : model->foundation->peek_stacks()) {
        stacks.push_back(s);
    }
    view->foundation->load_stacks(stacks);
    stacks.clear();
    for (const auto &s : model->tableau->peek_stacks()) {
        stacks.push_back(s);
    }
    view->tableau->load_stacks(stacks);
    view->deck->update(*model->deck);
    view->waste->update(*model->waste);
    view->apply_settings();
}

void Controller::restart_game() {
    model->restart();
    sync_view_with_model();
}
