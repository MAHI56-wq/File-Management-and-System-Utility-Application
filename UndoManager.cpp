#include "UndoManager.h"
#include <iostream>

void UndoManager::addAction(const std::string& type, const std::string& name) {
    actions.push_back({type, name});
}

void UndoManager::undoLast() {
    if(actions.empty()) {
        std::cout << "No actions to undo.\n";
        return;
    }
    UndoAction last = actions.back();
    actions.pop_back();
    std::cout << "Undid action: " << last.actionType << " -> " << last.targetName << "\n";
}

void UndoManager::listActions() const {
    std::cout << "Pending actions:\n";
    for(const auto& a : actions)
        std::cout << a.actionType << " -> " << a.targetName << "\n";
}

