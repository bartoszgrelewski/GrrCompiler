#include "code.hpp"

void Code::eq(Value *a, Value *b)
{
    debug_asm("COMP EQ");
    branchStack.push({});
    branchStack.top().push_back(CURR_PROGC);

    if (a->isNum)
    {
        if (b->isNum && a != b)
        {
            branchStack.top().push_back(CURR_PROGC);
            jump();
        }
        else
        {
            INIT_CHECK(b->id, "[comp eq]");
            EXISTS_CHECK(b->id, "[comp eq]");

            set(a->num);
            store(TMP_ADR);
            sub(ADR(b->id));
            branchStack.top().push_back(CURR_PROGC);
            jpos();
            load(ADR(b->id));
            sub(TMP_ADR);
            branchStack.top().push_back(CURR_PROGC);
            jpos();
        }
    }
    else
    {
        INIT_CHECK(a->id, "[comp eq]");
        EXISTS_CHECK(a->id, "[comp eq]");
        if (b->isNum)
        {
            set(b->num);
            store(TMP_ADR);
            sub(ADR(a->id));
            branchStack.top().push_back(CURR_PROGC);
            jpos();
            load(ADR(a->id));
            sub(TMP_ADR);
            branchStack.top().push_back(CURR_PROGC);
            jpos();
        }
        else
        {
            INIT_CHECK(b->id, "[comp eq]");
            EXISTS_CHECK(b->id, "[comp eq]");

            load(ADR(a->id));
            sub(ADR(b->id));
            branchStack.top().push_back(CURR_PROGC);
            jpos();
            load(ADR(b->id));
            sub(ADR(a->id));
            branchStack.top().push_back(CURR_PROGC);
            jpos();
        }
    }
}
void Code::neq(Value *a, Value *b)
{
    debug_asm("COMP NEQ");

    branchStack.push({});
    branchStack.top().push_back(CURR_PROGC);

    if (a->isNum)
    {
        if (b->isNum && a == b)
        {
            branchStack.top().push_back(CURR_PROGC);
            jump();
        }
        else
        {
            INIT_CHECK(b->id, "[comp neq]");
            EXISTS_CHECK(b->id, "[comp neq]");

            set(a->num);
            store(TMP_ADR);
            sub(ADR(b->id));
            jpos(CURR_PROGC + 4);
            load(ADR(b->id));
            sub(TMP_ADR);
            branchStack.top().push_back(CURR_PROGC);
            jzero();
        }
    }
    else
    {
        INIT_CHECK(a->id, "[comp neq]");
        EXISTS_CHECK(a->id, "[comp neq]");
        if (b->isNum)
        {
            set(b->num);
            store(TMP_ADR);
            sub(ADR(a->id));
            jpos(CURR_PROGC + 4);
            load(ADR(a->id));
            sub(TMP_ADR);
            branchStack.top().push_back(CURR_PROGC);
            jzero();
        }
        else
        {
            INIT_CHECK(b->id, "[comp neq]");
            EXISTS_CHECK(b->id, "[comp neq]");

            load(ADR(a->id));
            sub(ADR(b->id));
            jpos(CURR_PROGC + 4);
            load(ADR(b->id));
            sub(ADR(a->id));
            branchStack.top().push_back(CURR_PROGC);
            jzero();
        }
    }
}
void Code::le(Value *a, Value *b)
{
    debug_asm("COMP LE");

    branchStack.push({});
    branchStack.top().push_back(CURR_PROGC);

    if (a->isNum)
    {
        if (b->isNum && a >= b)
        {
            jump();
            branchStack.push({});
        }
        else
        {
            INIT_CHECK(b->id, "[comp le]");
            EXISTS_CHECK(b->id, "[comp le]");

            set(a->num);
            store(TMP_ADR);
            load(ADR(b->id));
            sub(TMP_ADR);
            branchStack.top().push_back(CURR_PROGC);
            jzero();
        }
    }
    else
    {
        INIT_CHECK(a->id, "[comp le]");
        EXISTS_CHECK(a->id, "[comp le]");
        if (b->isNum)
        {
            set(b->num);
            sub(ADR(a->id));
            branchStack.top().push_back(CURR_PROGC);
            jzero();
        }
        else
        {
            INIT_CHECK(b->id, "[comp le]");
            EXISTS_CHECK(b->id, "[comp le]");

            load(ADR(b->id));
            sub(ADR(a->id));
            branchStack.top().push_back(CURR_PROGC);
            jzero();
        }
    }
}
void Code::ge(Value *a, Value *b)
{
    debug_asm("COMP GE");

    branchStack.push({});
    branchStack.top().push_back(CURR_PROGC);

    if (a->isNum)
    {
        if (b->isNum && a <= b)
        {
            branchStack.top().push_back(CURR_PROGC);
            jump();
        }
        else
        {
            INIT_CHECK(b->id, "[comp ge]");
            EXISTS_CHECK(b->id, "[comp ge]");

            set(a->num);
            sub(ADR(b->id));
            branchStack.top().push_back(CURR_PROGC);
            jzero();
        }
    }
    else
    {
        INIT_CHECK(a->id, "[comp ge]");
        EXISTS_CHECK(a->id, "[comp ge]");
        if (b->isNum)
        {
            set(b->num);
            store(TMP_ADR);
            load(ADR(a->id));
            sub(TMP_ADR);
            branchStack.top().push_back(CURR_PROGC);
            jzero();
        }
        else
        {
            INIT_CHECK(b->id, "[comp ge]");
            EXISTS_CHECK(b->id, "[comp ge]");

            load(ADR(a->id));
            sub(ADR(b->id));
            branchStack.top().push_back(CURR_PROGC);
            jzero();
        }
    }
}
void Code::leq(Value *a, Value *b)
{
    debug_asm("COMP LEQ");

    branchStack.push({});
    branchStack.top().push_back(CURR_PROGC);

    if (a->isNum)
    {
        if (b->isNum && a > b)
        {
            branchStack.top().push_back(CURR_PROGC);
            jump();
        }
        else
        {
            INIT_CHECK(b->id, "[comp leq]");
            EXISTS_CHECK(b->id, "[comp leq]");

            set(a->num);
            sub(ADR(b->id));
            branchStack.top().push_back(CURR_PROGC);
            jpos();
        }
    }
    else
    {
        INIT_CHECK(a->id, "[comp leq]");
        EXISTS_CHECK(a->id, "[comp leq]");
        if (b->isNum)
        {
            set(b->num);
            store(TMP_ADR);
            load(ADR(a->id));
            sub(TMP_ADR);
            branchStack.top().push_back(CURR_PROGC);
            jpos();
        }
        else
        {
            INIT_CHECK(b->id, "[comp leq]");
            EXISTS_CHECK(b->id, "[comp leq]");

            load(ADR(a->id));
            sub(ADR(b->id));
            branchStack.top().push_back(CURR_PROGC);
            jpos();
        }
    }
}
void Code::geq(Value *a, Value *b)
{
    debug_asm("COMP GEQ");

    branchStack.push({});
    branchStack.top().push_back(CURR_PROGC);

    if (a->isNum)
    {
        if (b->isNum && a < b)
        {
            branchStack.top().push_back(CURR_PROGC);
            jump();
        }
        else
        {
            INIT_CHECK(b->id, "[comp geq]");
            EXISTS_CHECK(b->id, "[comp geq]");

            set(a->num);
            store(TMP_ADR);
            load(ADR(b->id));
            sub(TMP_ADR);
            branchStack.top().push_back(CURR_PROGC);
            jpos();
        }
    }
    else
    {
        INIT_CHECK(a->id, "[comp geq]");
        EXISTS_CHECK(a->id, "[comp geq]");
        if (b->isNum)
        {

            set(b->num);
            sub(ADR(a->id));
            branchStack.top().push_back(CURR_PROGC);
            jpos();
        }
        else
        {
            INIT_CHECK(b->id, "[comp geq]");
            EXISTS_CHECK(b->id, "[comp geq]");

            load(ADR(b->id));
            sub(ADR(a->id));
            branchStack.top().push_back(CURR_PROGC);
            jpos();
        }
    }
}