#include "code.hpp"

Value *Code::plus(Value *a, Value *b)
{
    debug("Adding \"" << a->id << "\"/" << a->num << " + \"" << b->id << "\"/" << b->num << "[plus]");

    if (a->isNum)
    {
        if (b->isNum)
            return new Value(a->num + b->num);

        INIT_CHECK(b->id, "[plus]");
        EXISTS_CHECK(b->id, "[plus]");

        set(a->num);
        add(ADR(b->id));
        store(TMP_ADR);
    }
    else
    {
        INIT_CHECK(a->id, "[plus]");
        EXISTS_CHECK(a->id, "[plus]");
        if (b->isNum)
        {
            set(b->num);
            add(ADR(a->id));
            store(TMP_ADR);
        }
        else
        {
            INIT_CHECK(b->id, "[plus]");
            EXISTS_CHECK(b->id, "[plus]");

            load(ADR(b->id));
            add(ADR(a->id));
            store(TMP_ADR);
        }
    }
    return new Value("-TMP");
}

Value *Code::minus(Value *a, Value *b)
{
    debug("Subtracting \"" << a->id << "\"/" << a->num << " - \"" << b->id << "\"/" << b->num << "[minus]");

    if (a->isNum)
    {
        if (b->isNum)
        {
            long long x = a->num - b->num;
            return new Value(x > 0 ? x : 0);
        }

        INIT_CHECK(b->id, "[plus]");
        EXISTS_CHECK(b->id, "[plus]");

        set(a->num);
        sub(ADR(b->id));
        store(TMP_ADR);
    }
    else
    {
        INIT_CHECK(a->id, "[plus]");
        EXISTS_CHECK(a->id, "[plus]");
        if (b->isNum)
        {
            set(b->num);
            store(TMP_ADR);
            load(ADR(a->id));
            sub(TMP_ADR);
            store(TMP_ADR);
        }
        else
        {
            INIT_CHECK(b->id, "[plus]");
            EXISTS_CHECK(b->id, "[plus]");

            load(ADR(a->id));
            sub(ADR(b->id));
            store(TMP_ADR);
        }
    }
    return new Value("-TMP");
}

Value *Code::times(Value *a, Value *b)
{
    debug("Multiplying \"" << a->id << "\"/" << a->num << " - \"" << b->id << "\"/" << b->num << "[times]");

    if (a->isNum)
    {
        if (b->isNum)
        {
            return new Value(a->num * b->num);
        }

        INIT_CHECK(b->id, "[times]");
        EXISTS_CHECK(b->id, "[times]");

        // a = const, so we set and store it
        set(a->num);
        store(TMP_ADR);
        // b = variable, so we load and store it
        load(ADR(b->id));
        store(TMP_ADR_2);
    }
    else
    {
        INIT_CHECK(a->id, "[times]");
        EXISTS_CHECK(a->id, "[times]");

        load(ADR(a->id));
        store(TMP_ADR);

        if (b->isNum)
        {
            set(b->num);
            store(TMP_ADR_2);
        }
        else
        {
            INIT_CHECK(b->id, "[times]");
            EXISTS_CHECK(b->id, "[times]");

            load(ADR(b->id));
            store(TMP_ADR_2);
        }
    }

    if (mul_adr != -1)
    {
        set(CURR_PROGC + 3);
        store(TMP_ADR_9);
        jump(mul_adr);
        return new Value("-TMP3");
    }

    set(CURR_PROGC + 33);
    store(TMP_ADR_9);
    mul_adr = CURR_PROGC;

    set(0);
    store(TMP_ADR_3); // store 0 in TMP_ADR_3
    set(1);
    store(TMP_ADR_4); // store 1 in TMP_ADR_4

    // Starting Russian Peasant Multiplication Algorithm
    // Time Complexity O(log n)

    debug_asm("WHILE accumulator is equal to 0 DO");
    const unsigned long long BeginLoop = CURR_PROGC;
    load(TMP_ADR_2);
    jzero(CURR_PROGC + 24);
    debug_asm("Check IF temp2 is odd");
    sub(TMP_ADR_4);
    debug_asm("jump if temp2 is equal to 1");
    jzero(CURR_PROGC + 19);
    load(TMP_ADR_2);
    half();
    store(TMP_ADR_5);
    add(TMP_ADR_5);
    store(TMP_ADR_5);
    load(TMP_ADR_2);
    sub(TMP_ADR_5);
    debug_asm("jump if temp2 is even");
    jzero(CURR_PROGC + 4);
    debug_asm("if temp2 is odd, then add temp1 to result");
    load(TMP_ADR_3);
    add(TMP_ADR);
    store(TMP_ADR_3);
    debug_asm("mult temp1 by 2");
    load(TMP_ADR);
    add(TMP_ADR);
    store(TMP_ADR);
    debug_asm("divide temp2 by 2");
    load(TMP_ADR_2);
    half();
    store(TMP_ADR_2);
    debug_asm("jump to WHILE");
    jump(BeginLoop); // jump to WHILE
    load(TMP_ADR_3);
    add(TMP_ADR);
    store(TMP_ADR_3);
    jumpi(TMP_ADR_9);

    return new Value("-TMP3");
}

Value *Code::div(Value *a, Value *b)
{
    debug("Dividing \"" << a->id << "\"/" << a->num << " - \"" << b->id << "\"/" << b->num << "[div]");

    if (a->isNum)
    {
        if (b->isNum)
        {
            return new Value((b->num != 0) ? (a->num / b->num) : 0);
        }

        INIT_CHECK(b->id, "[div]");
        EXISTS_CHECK(b->id, "[div]");

        // a = const, so we set and store it
        set(a->num);
        store(TMP_ADR_2);
        store(TMP_ADR_5);
        // b = variable, so we load and store it
        load(ADR(b->id));
        store(TMP_ADR);
        store(TMP_ADR_4);
    }
    else
    {
        INIT_CHECK(a->id, "[div]");
        EXISTS_CHECK(a->id, "[div]");

        load(ADR(a->id));
        store(TMP_ADR_2);
        store(TMP_ADR_5);

        if (b->isNum)
        {
            set(b->num);
            store(TMP_ADR);
            store(TMP_ADR_4);
        }
        else
        {
            INIT_CHECK(b->id, "[div]");
            EXISTS_CHECK(b->id, "[div]");

            load(ADR(b->id));
            store(TMP_ADR);
            store(TMP_ADR_4);
        }
    }

    set(1);
    store(TMP_ADR_3);
    store(TMP_ADR_7);
    set(0);
    store(TMP_ADR_6);
    store(TMP_ADR_8);
    load(TMP_ADR);
    const unsigned long long FirstJump = CURR_PROGC;
    jzero(FirstJump + 54);
    sub(TMP_ADR_2);
    jzero(FirstJump + 5);
    set(0);
    jump(FirstJump + 54);
    const unsigned long long StartLoop = CURR_PROGC;
    load(TMP_ADR_5);
    sub(TMP_ADR_4);
    jzero(CURR_PROGC + 8);
    load(TMP_ADR_3);
    add(TMP_ADR_3);
    store(TMP_ADR_3);
    load(TMP_ADR_4);
    add(TMP_ADR_4);
    store(TMP_ADR_4);
    jump(StartLoop);
    load(TMP_ADR_4);
    sub(TMP_ADR_5);
    jpos(CURR_PROGC + 31);
    load(TMP_ADR_5);
    sub(TMP_ADR_4);
    store(TMP_ADR_5);
    load(TMP_ADR_6);
    add(TMP_ADR_3);
    store(TMP_ADR_6);
    jump(CURR_PROGC + 31);
    const unsigned long long AddToSum = CURR_PROGC;
    load(TMP_ADR_4);
    half();
    store(TMP_ADR_4);
    jpos(CURR_PROGC + 3);
    load(TMP_ADR);
    store(TMP_ADR_4);
    load(TMP_ADR_5);
    sub(TMP_ADR_4);
    store(TMP_ADR_5);
    load(TMP_ADR_3);
    half();
    store(TMP_ADR_3);
    jpos(CURR_PROGC + 3);
    set(1);
    store(TMP_ADR_3);
    load(TMP_ADR_6);
    add(TMP_ADR_3);
    store(TMP_ADR_6);
    set(1);
    store(TMP_ADR_3);
    load(TMP_ADR);
    store(TMP_ADR_4);
    jump(StartLoop);
    load(TMP_ADR_3);
    sub(TMP_ADR_7);
    jzero(CURR_PROGC + 5);
    jump(AddToSum);
    load(TMP_ADR_6);
    add(TMP_ADR_4);
    store(TMP_ADR_6);
    load(TMP_ADR_6);
    store(TMP_ADR);

    return new Value("-TMP");
}

Value *Code::mod(Value *a, Value *b)
{
    debug("Mod \"" << a->id << "\"/" << a->num << " - \"" << b->id << "\"/" << b->num << "[mod]");

    if (a->isNum)
    {
        if (b->isNum)
        {
            return new Value((b->num != 0) ? (a->num % b->num) : 0);
            // return new Value( a->num / b->num );
        }

        INIT_CHECK(b->id, "[mod]");
        EXISTS_CHECK(b->id, "[mod]");

        // a = const, so we set and store it
        set(a->num);
        store(TMP_ADR_2);
        store(TMP_ADR_5);
        // b = variable, so we load and store it
        load(ADR(b->id));
        store(TMP_ADR);
        store(TMP_ADR_4);
    }
    else
    {
        INIT_CHECK(a->id, "[mod]");
        EXISTS_CHECK(a->id, "[mod]");

        load(ADR(a->id));
        store(TMP_ADR_2);
        store(TMP_ADR_5);

        if (b->isNum)
        {
            set(b->num);
            store(TMP_ADR);
            store(TMP_ADR_4);
        }
        else
        {
            INIT_CHECK(b->id, "[mod]");
            EXISTS_CHECK(b->id, "[mod]");

            load(ADR(b->id));
            store(TMP_ADR);
            store(TMP_ADR_4);
        }
    }

    // TMP_ADR_2 % TMP_ADR_4

    neq(new Value("-TMP4"), new Value(0));

    // repair TMP_ARD reg

    assign("-TMP", new Value("-TMP4"));

    set(1);
    store(TMP_ADR_3);
    store(TMP_ADR_7);
    set(0);
    store(TMP_ADR_6);
    store(TMP_ADR_8);
    load(TMP_ADR);
    const unsigned long long FirstJump = CURR_PROGC;
    jzero(FirstJump + 54);
    sub(TMP_ADR_2);
    jzero(FirstJump + 5);
    set(0);
    jump(FirstJump + 54);
    const unsigned long long StartLoop = CURR_PROGC;
    load(TMP_ADR_5);
    sub(TMP_ADR_4);
    jzero(CURR_PROGC + 8);
    load(TMP_ADR_3);
    add(TMP_ADR_3);
    store(TMP_ADR_3);
    load(TMP_ADR_4);
    add(TMP_ADR_4);
    store(TMP_ADR_4);
    jump(StartLoop);
    load(TMP_ADR_4);
    sub(TMP_ADR_5);
    jpos(CURR_PROGC + 31);
    load(TMP_ADR_5);
    sub(TMP_ADR_4);
    store(TMP_ADR_5);
    load(TMP_ADR_6);
    add(TMP_ADR_3);
    store(TMP_ADR_6);
    jump(CURR_PROGC + 31);
    const unsigned long long AddToSum = CURR_PROGC;
    load(TMP_ADR_4);
    half();
    store(TMP_ADR_4);
    jpos(CURR_PROGC + 3);
    load(TMP_ADR);
    store(TMP_ADR_4);
    load(TMP_ADR_5);
    sub(TMP_ADR_4);
    store(TMP_ADR_5);
    load(TMP_ADR_3);
    half();
    store(TMP_ADR_3);
    jpos(CURR_PROGC + 3);
    set(1);
    store(TMP_ADR_3);
    load(TMP_ADR_6);
    add(TMP_ADR_3);
    store(TMP_ADR_6);
    set(1);
    store(TMP_ADR_3);
    load(TMP_ADR);
    store(TMP_ADR_4);
    jump(StartLoop);
    load(TMP_ADR_3);
    sub(TMP_ADR_7);
    jzero(CURR_PROGC + 5);
    jump(AddToSum);
    load(TMP_ADR_6);
    add(TMP_ADR_4);
    store(TMP_ADR_6);
    load(TMP_ADR_5);
    store(TMP_ADR);
    ifBlock();

    return new Value("-TMP");
}