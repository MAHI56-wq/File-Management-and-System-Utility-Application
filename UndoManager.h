#ifndef UNDO_MANAGER_H
#define UNDO_MANAGER_H

#include <string>
#include <vector>

struct UndoAction {
    std::string actionType;
    std::string targetName;
};

class UndoManager {
private:
    std::vector<UndoAction> actions;
public:
    void addAction(const std::string& type, const std::string& name);
    void undoLast();
    void listActions() const;
};

#endif 

