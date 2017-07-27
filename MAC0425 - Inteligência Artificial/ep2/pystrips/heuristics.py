import util
import sys
from functools import reduce
from operator import add

def h_naive(state, planning):
    return 0


def h_add(state, planning):
    '''
    Return heuristic h_add value for `state`.

    OBSERVATION: It receives `planning` object in order
    to access the applicable actions and problem information.
    '''
    h = {}

    for p in planning.problem.goal:
        h[p] = sys.maxsize

    for p in state:
        h[p] = 0

    X = set (state)
    stop = False

    while not stop:
        actions = planning.applicable (X)

        if len(actions) == 0:
            return sys.maxsize

        for action in actions:
            X = X | action.pos_effect
            sumOfH = reduce (add, map (lambda x: h[x], action.precond), 0)

            for p in action.pos_effect:
                if p not in h:
                    h[p] = sys.maxsize

                if h[p] <= 1 + sumOfH:
                    stop = True
                    break
                else:
                    h[p] = 1 + sumOfH

            if stop:
                break

    return reduce (add, map (lambda x: h[x], state), 0)

def h_max(state, planning):
    '''
    Return heuristic h_max value for `state`.

    OBSERVATION: It receives `planning` object in order
    to access the applicable actions and problem information.
    '''
    h = {}

    for p in planning.problem.goal:
        h[p] = sys.maxsize

    for p in state:
        h[p] = 0

    X = set (state)
    stop = False

    while not stop:
        actions = planning.applicable (X)

        if len(actions) == 0:
            return sys.maxsize

        for action in actions:
            X = X | action.pos_effect
            sumOfH = reduce (add, map (lambda x: h[x], action.precond), 0)

            for p in action.pos_effect:
                if p not in h:
                    h[p] = sys.maxsize

                if h[p] <= 1 + sumOfH:
                    stop = True
                    break
                else:
                    h[p] = 1 + sumOfH

            if stop:
                break

    return reduce (max, map (lambda x: h[x], state), 0)


def h_ff(state, planning):
    '''
    Return heuristic h_ff value for `state`.

    OBSERVATION: It receives `planning` object in order
    to access the applicable actions and problem information.
    '''
    util.raiseNotDefined()
    ' YOUR CODE HERE '
