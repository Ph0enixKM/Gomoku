#include <include.h>

void createEnd() {
    UI vbox = UICreateVBox(true);
    ui_verdict = UICreateLabel("");
    UIAppend(vbox, ui_verdict);
    UISetID(vbox, "jumbo");
    UIStackAdd(ui_stack, vbox, scene_end);
}