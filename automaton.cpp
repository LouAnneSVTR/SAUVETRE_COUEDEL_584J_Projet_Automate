/**
 * \file automaton.cpp
 * \brief Implementation file containing the code for the functions that could not be implemented in "automaton.hpp"
 * \author Matthieu Perrin 
 * \version 1
 * \date 11-16-2020
 */

#include "automaton.hpp"
#include "set.hpp"
#include <iostream>

using namespace univ_nantes;

automaton automaton::determine() const {
  /* TODO: Question 1. retourner un automate déterminisé équivalent
   *
   * indice : utiliser un objet de type std::vector<set<int>> pour stocker
   * les ensembles d'états créés par l'algorithme de déterminisation.
   * Les états de l'automate déterministe retourné seront les indices
   * des ensembles d'états dans le vecteur. */

    //Variable
    std::vector<set<int>> states_newAutomate;
    set<char> alphabet;
    set<transition> newTrans;
    set<int> newSet;
    set<int> state;

    //Début
    if ( automaton.is_deterministic ) {
        std::cout << "Cet automate est déjà deterministe, il est inutile d'appliquer la fonction ! " << endl;

    } else {
        state_newAutomate[0] = epsilon_accessible( this->initials);
        //On insère dans le premier set tous les états initiaux du "this".
        //On ajoute toutes les éventuelles E-transition dans l'état initial du nouvel automate.

        alphabet = this->get_alphabet(); //On cherche l'alphabet du "this".

        for (int  i = 0 ; i < state_newAutomate.size() ; ++i) {
            state = states_newAutomate[i];

            for (char a : alphabet) {
                newSet |= accessible(state, a);

                if( newSet.size() != 0 ) { //On test si

                }
                //TODO voir etat si il est final
               // checher si sons sous ensemble est deja dans mes new state et avec k l
                //indicesi le sous ensmeble est deja ^résent, on ne le rajoute


                /* bool notFound = true;
                int k = 0;

                while (notFound && k < newStates.size()) {
                    if (newStates[k] == newSet) {
                        notFound = false;
                    } else {
                        k++;
                    }
                }
                if (notFound) {
                    newStates.push_back(newSet); // on ajoute le nouveau sous-ensemble
                    newTransitions |= transition(i, a, newStates.size() -
                                                       1); // on crée la nouvelle transition de l'automate déterministe
                    bool final;
                    for (int s : newSet) {
                        final = this->finals.contains(s);
                    }
                    if (final) {
                        newFinals |= newStates.size() - 1;
                    }
                } else {
                    newTransitions |= transition(i, a,
                                                 k);// on crée la nouvelle transition de l'automate déterministe
                }

            }
        }
    }*/
            }
        }


        //TODO 2- Trouver un moyen de choper les elements pour regrouper les transitions du futur automate
        // on peut s'aider le méthode size()

        //TODO 3- RECREER en commencer a partir de l'éatat initial tous les nouveaux etats de l'automate determiniqtes
        // todo → faire attention a prendre les états qui menent vers les bonnes transiont avec le bon carac ET permi eux, ajouter leur E-transitions
        //todo → Faire attention a ne pas recreer un état de l'automate deterministe deja existant dans le vector de set ETATS
        //→ utiliser le méthode de comparaison set operator==

        //TODO 4- RECREER les transitions de l'automate, PAS 2 TRANSITIONS PAREILS

        /*
         * while(count < newStates.size()) {
         * for (char term : this->get_alphabet()){
          // pour chaque état et pour chaque charactère de l'alphabet,
          // on créer un set d'état de sortie
         * for (transition trans : this->transitions) {
          // on parcours toutes les transitions de l'automate
         * while (i < state.size()) {
         * for (set<int> y : newStates) {
         */
    }
    return *this;
}


/*
 * Gets whether the automaton is deterministic or not
 *
 * An automaton is considered to be deterministic if, and only if, it has exactly one initial state, no epsilon-transition, 
 * and no two transitions starting in the same state and ending in a different states, with a different label.
 */
bool automaton::is_deterministic() const {
  // Check that there is a unique initial state
  if(initials.size() != 1) return false;
  for(transition t1 : transitions) {
    // Check that there is no epsilon transition
    if(t1.is_epsilon()) return false;
    for(transition t2 : transitions) {
      // Check that there are no two transitions starting in the same state, with the same label
      if(t1.start == t2.start && t1.terminal == t2.terminal && t1.end != t2.end) return false;
    }
  }
  return true;
}

/**
 * Gets the set of states accessible from some state in from by following epsilon transitions
 * 
 * A state y is included in the returned set if, and only if, there exists a state x in from 
 * and a sequence of states x0=x, x1, ..., xn = y such that each epsilon-transition xi |--> x(i+1)
 * is contained in transitions.
 *
 * Example : a.epsilon_accessible(a.initials) returns all states accessible in a, through the empty word. 
 */
set<int> automaton::epsilon_accessible(set<int> from) const {
  set<int> result = from;
  bool go_on = true;
  while (go_on) {
    go_on = false;
    for(transition t : transitions) {
      if(result.contains(t.start) && t.terminal == '\0' && !result.contains(t.end)) {
	result |= t.end;
	go_on = true;
      }
    }
  }
  return result;
}

/**
 * Gets the set of states accessible from some state in from by following one transition labeled by c 
 *
 * A state y is included in the returned set if, and only if, there exists a state x in from 
 * such that x |-c-> y is contained in transitions.
 *
 * Example : a.epsilon_accessible(a.accessible(a.epsilon_accessible({1,2}),'a')) returns all states accessible in a, from states 1 or 2, through the word "a". 
 */
set<int> automaton::accessible(set<int> from, char c) const {
  set<int> result;
  for(transition t : transitions) {
    if(from.contains(t.start) && t.terminal == c)
      result |= t.end;
  }
  return result;
}

/*
 * Returns the set of states of the automaton, including all states accessible from the initial states
 *
 * A state is contained in the set returned if it is contained in initials, finals, or at the start or and of any transition.
 */
set<int> automaton::get_states() const {
  set<int> states = initials | finals;
  for(transition t : transitions)
    states |= {t.start, t.end};
  return states;
}

/*
 * Returns the set of terminal symbols (lower-case letters) that label at least one transition of the automaton
 */
set<char> automaton::get_alphabet() const {
  set<char> alphabet;
  for(transition t : transitions)
    if(!t.is_epsilon())
      alphabet |= {t.terminal};
  return alphabet;
}
