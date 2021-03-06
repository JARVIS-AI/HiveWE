#pragma once

#include <QMainWindow>

#include "ui_ObjectEditor.h"

#include "TableModel.h"
#include "UnitTreeModel.h"
#include "DoodadTreeModel.h"
#include "DestructibleTreeModel.h"
#include "AbilityTreeModel.h"
#include "ItemTreeModel.h"
#include "BuffTreeModel.h"
#include "UpgradeTreeModel.h"
#include "DockManager.h"
#include "DockAreaWidget.h"
#include <QTreeView>

class ObjectEditor : public QMainWindow {
	Q_OBJECT

public:
	ObjectEditor(QWidget* parent = nullptr);

private:
	Ui::ObjectEditor ui;

	ads::CDockManager* dock_manager = new ads::CDockManager();
	ads::CDockAreaWidget* dock_area = nullptr;

	QTreeView* unit_explorer = new QTreeView;
	QTreeView* doodad_explorer = new QTreeView;
	QTreeView* item_explorer = new QTreeView;
	QTreeView* destructible_explorer = new QTreeView;
	QTreeView* ability_explorer = new QTreeView;
	QTreeView* upgrade_explorer = new QTreeView;
	QTreeView* buff_explorer = new QTreeView;
	
	UnitTreeModel* unitTreeModel;
	DoodadTreeModel* doodadTreeModel;
	DestructibleTreeModel* destructibleTreeModel;
	AbilityTreeModel* abilityTreeModel;
	ItemTreeModel* itemTreeModel;
	BuffTreeModel* buffTreeModel;
	UpgradeTreeModel* upgradeTreeModel;

	QSortFilterProxyModel* unitTreeFilter;
	QSortFilterProxyModel* doodadTreeFilter;
	QSortFilterProxyModel* destructibleTreeFilter;
	QSortFilterProxyModel* abilityTreeFilter;
	QSortFilterProxyModel* itemTreeFilter;
	QSortFilterProxyModel* buffTreeFilter;
	QSortFilterProxyModel* upgradeTreeFilter;

	std::shared_ptr<QIconResource> custom_unit_icon;
	std::shared_ptr<QIconResource> custom_item_icon;
	std::shared_ptr<QIconResource> custom_doodad_icon;
	std::shared_ptr<QIconResource> custom_destructible_icon;
	std::shared_ptr<QIconResource> custom_ability_icon;
	std::shared_ptr<QIconResource> custom_buff_icon;
	std::shared_ptr<QIconResource> custom_upgrade_icon;

	enum class Category {
		unit,
		doodad,
		item,
		destructible,
		ability,
		upgrade,
		buff
	};

	void item_clicked(QSortFilterProxyModel* model, const QModelIndex& index, Category category);
};