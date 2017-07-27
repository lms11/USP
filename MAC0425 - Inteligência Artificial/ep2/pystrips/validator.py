import util
from state import State


def validate(problem, solution):
    '''
    Return true if `solution` is a valid plan for `problem`.
    Otherwise, return false.

    OBSERVATION: you should check action applicability,
    next-state generation and if final state is indeed a goal state.
    It should give you some indication of the correctness of your planner,
    mainly for debugging purposes.
    '''
    state = problem.init

    for action in solution:
        if not action.precond <= set (state):
            return False

        for neg_effect in action.neg_effect:
            if neg_effect in state:
                state.remove (neg_effect)

        for pos_effect in action.pos_effect:
            state.add (pos_effect)

    return True
