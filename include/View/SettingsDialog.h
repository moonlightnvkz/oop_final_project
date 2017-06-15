//
// Created by moonlightnvkz on 11.06.17.
//

#pragma once

#include <QDialog>

class QTabWidget;
class QDialogButtonBox;
class QSlider;
class QComboBox;
class QCheckBox;
class QSpinBox;
class QAbstractButton;


class AppearanceTab : public QWidget {
    Q_OBJECT
public:
    explicit AppearanceTab(QWidget *parent = nullptr);

    virtual ~AppearanceTab() override;

public slots:
    void on_choose_color();

protected:
    void load();

    QSlider *foundation_h_space_slider;

    QSlider *tableau_h_space_slider;

    QSlider *tableau_v_space_slider;

    QPushButton *color_button;

    friend class SettingsDialog;
};


class GameRulesTab : public QWidget {
    Q_OBJECT
public:
    explicit GameRulesTab(QWidget *parent = nullptr);

    virtual ~GameRulesTab() override;

    bool changed() const { return m_changed; }

public slots:
    void on_change(const int);

protected:
    void load();

    QSpinBox *tableau_stack_amount_box;

    QCheckBox *tableau_stack_suit_alternation_box;

    QComboBox *tableau_stack_rank_order_box;

    QComboBox *foundation_stack_rank_order_box;

    friend class SettingsDialog;

    bool m_changed;
};

class SettingsDialog : public QDialog {
Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = nullptr);

    virtual ~SettingsDialog() override;

    bool game_rules_changed() const { return game_rules_tab->changed(); }

public slots:
    void on_accepted();

    void on_restore_defaults(QAbstractButton *btn);

protected:
    QTabWidget *tab_widget;

    QDialogButtonBox *button_box;

    AppearanceTab *appearance_tab;

    GameRulesTab *game_rules_tab;
};
