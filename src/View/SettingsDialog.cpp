//
// Created by moonlightnvkz on 11.06.17.
//

#include <QTabWidget>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QColorDialog>
#include "include/Settings.h"
#include "include/View/SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent)
        : QDialog(parent) {
    tab_widget = new QTabWidget(this);
    appearance_tab = new AppearanceTab(this);
    tab_widget->addTab(appearance_tab, "Appearance");
    game_rules_tab = new GameRulesTab(this);
    tab_widget->addTab(game_rules_tab, "Game Rules");

    button_box = new QDialogButtonBox(QDialogButtonBox::Ok
                                      | QDialogButtonBox::Cancel
                                      | QDialogButtonBox::RestoreDefaults, this);
    connect(button_box, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(button_box, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(button_box, &QDialogButtonBox::clicked, this, &SettingsDialog::on_restore_defaults);
    connect(this, &QDialog::accepted, this, &SettingsDialog::on_accepted);

    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->addWidget(tab_widget);
    main_layout->addWidget(button_box);
    setLayout(main_layout);

    setWindowTitle("Settings");
}

SettingsDialog::~SettingsDialog() {

}

void SettingsDialog::on_accepted() {
    Settings &settings = Settings::GetInstance();
    QString str;
    settings.game_rules.alternate_suits_in_the_tableau =
            game_rules_tab->tableau_stack_suit_alternation_box->isChecked();
    str = game_rules_tab->foundation_stack_rank_order_box->currentText();
    settings.game_rules.foundation_rank_order = str == "Ascending"
                                                ? Settings::GameRules::RankOrder::Ascending
                                                : Settings::GameRules::RankOrder::Descending;
    str = game_rules_tab->tableau_stack_rank_order_box->currentText();
    settings.game_rules.tableau_rank_order = str == "Ascending"
                                                ? Settings::GameRules::RankOrder::Ascending
                                                : Settings::GameRules::RankOrder::Descending;
    settings.game_rules.tableau_stacks_amount =
            static_cast<unsigned>(game_rules_tab->tableau_stack_amount_box->value());

    settings.appearance.foundation_spacing = appearance_tab->foundation_h_space_slider->value();
    settings.appearance.tableau_spacing = appearance_tab->tableau_h_space_slider->value();
    settings.appearance.tableau_shift = appearance_tab->tableau_v_space_slider->value();
    const QColor &color = appearance_tab->color_button->palette().color(QPalette::Button);
    settings.appearance.background_color = {color.red(), color.green(), color.blue()};
}

void SettingsDialog::on_restore_defaults(QAbstractButton *btn) {
    if (btn != static_cast<QAbstractButton*>(button_box->button(QDialogButtonBox::RestoreDefaults))) {
        return;
    }
    Settings::GetInstance().load_default();
    appearance_tab->load();
    game_rules_tab->load();
}

AppearanceTab::AppearanceTab(QWidget *parent)
        : QWidget(parent) {
    QLabel *foundation_h_space_label = new QLabel("Foundation spacing:", this);
    foundation_h_space_slider = new QSlider(Qt::Horizontal, this);
    foundation_h_space_slider->setRange(0, 100);

    QLabel *tableau_h_space_label = new QLabel("Tableau spacing:", this);
    tableau_h_space_slider = new QSlider(Qt::Horizontal, this);
    tableau_h_space_slider->setRange(0, 100);

    QLabel *tableau_v_space_label = new QLabel("Tableau shift:", this);
    tableau_v_space_slider = new QSlider(Qt::Horizontal, this);
    tableau_v_space_slider->setRange(0, 50);

    QLabel *background_color_label = new QLabel("Background color:");
    color_button = new QPushButton(this);
    color_button->setAutoFillBackground(true);
    color_button->setFixedSize(25, 25);
    connect(color_button, &QPushButton::clicked, this, &AppearanceTab::on_choose_color);

    load();

    QGridLayout *main_layout = new QGridLayout(this);
    main_layout->addWidget(foundation_h_space_label, 0, 0, Qt::AlignLeft);
    main_layout->addWidget(foundation_h_space_slider, 0, 1, Qt::AlignCenter);
    main_layout->addWidget(tableau_h_space_label, 1, 0, Qt::AlignLeft);
    main_layout->addWidget(tableau_h_space_slider, 1, 1, Qt::AlignCenter);
    main_layout->addWidget(tableau_v_space_label, 2, 0, Qt::AlignLeft);
    main_layout->addWidget(tableau_v_space_slider, 2, 1, Qt::AlignCenter);
    main_layout->addWidget(background_color_label, 3, 0, Qt::AlignCenter);
    main_layout->addWidget(color_button, 3, 1, Qt::AlignCenter);
    setLayout(main_layout);
}

AppearanceTab::~AppearanceTab() {

}

void AppearanceTab::load() {
    Settings::Appearance &appearance = Settings::GetInstance().appearance;
    foundation_h_space_slider->setValue(appearance.foundation_spacing);
    tableau_h_space_slider->setValue(appearance.tableau_spacing);
    tableau_v_space_slider->setValue(appearance.tableau_shift);
    QPalette palette = color_button->palette();
    palette.setColor(QPalette::Button, QColor(appearance.background_color.red,
                                              appearance.background_color.green,
                                              appearance.background_color.blue));
    color_button->setPalette(palette);
}

void AppearanceTab::on_choose_color() {
    QColor color;
    color = QColorDialog::getColor(color_button->palette().color(QPalette::Button), this, "Select Color");

    QPalette palette = color_button->palette();
    palette.setColor(QPalette::Button, color);
    color_button->setPalette(palette);
}

GameRulesTab::GameRulesTab(QWidget *parent)
        : QWidget(parent) {
    QLabel *tableau_stack_amount_label = new QLabel("Tableau stack amount:", this);
    tableau_stack_amount_box = new QSpinBox(this);
    tableau_stack_amount_box->setRange(1, 10);

    QLabel *tableau_stack_suit_alternation_label = new QLabel("Alternate suits in the tableau", this);
    tableau_stack_suit_alternation_box = new QCheckBox(this);

    QLabel *tableau_stack_rank_order_label = new QLabel("Tableau rank order:", this);
    tableau_stack_rank_order_box = new QComboBox(this);
    tableau_stack_rank_order_box->addItem("Ascending");
    tableau_stack_rank_order_box->addItem("Descending");

    QLabel *foundation_stack_rank_order_label = new QLabel("Foundation rank order:", this);
    foundation_stack_rank_order_box = new QComboBox(this);
    foundation_stack_rank_order_box->addItem("Ascending");
    foundation_stack_rank_order_box->addItem("Descending");

    load();

    QGridLayout *main_layout = new QGridLayout(this);
    main_layout->addWidget(tableau_stack_amount_label, 0, 0, Qt::AlignLeft);
    main_layout->addWidget(tableau_stack_amount_box, 0, 1, Qt::AlignCenter);
    main_layout->addWidget(tableau_stack_suit_alternation_label, 1, 0, Qt::AlignLeft);
    main_layout->addWidget(tableau_stack_suit_alternation_box, 1, 1, Qt::AlignCenter);
    main_layout->addWidget(tableau_stack_rank_order_label, 2, 0, Qt::AlignLeft);
    main_layout->addWidget(tableau_stack_rank_order_box, 2, 1, Qt::AlignCenter);
    main_layout->addWidget(foundation_stack_rank_order_label, 3, 0, Qt::AlignLeft);
    main_layout->addWidget(foundation_stack_rank_order_box, 3, 1, Qt::AlignCenter);

    connect(tableau_stack_amount_box, SIGNAL(valueChanged(int)), this, SLOT(on_change(int)));
    connect(tableau_stack_suit_alternation_box, SIGNAL(stateChanged(int)), this, SLOT(on_change(int)));
    connect(tableau_stack_rank_order_box, SIGNAL(currentIndexChanged(int)), this, SLOT(on_change(int)));
    connect(foundation_stack_rank_order_box, SIGNAL(currentIndexChanged(int)), this, SLOT(on_change(int)));
    setLayout(main_layout);
    m_changed = false;
}

GameRulesTab::~GameRulesTab() {

}


void GameRulesTab::on_change(int) {
    m_changed = true;
}

void GameRulesTab::load() {
    Settings &settings = Settings::GetInstance();
    tableau_stack_amount_box->setValue(settings.game_rules.tableau_stacks_amount);
    tableau_stack_suit_alternation_box->setChecked(settings.game_rules.alternate_suits_in_the_tableau);
    tableau_stack_rank_order_box->setCurrentIndex(static_cast<int>(settings.game_rules.tableau_rank_order));
    foundation_stack_rank_order_box->setCurrentIndex(static_cast<int>(settings.game_rules.foundation_rank_order));
}