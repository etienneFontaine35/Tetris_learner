/*

Possible actions : LEFT, RIGHT, ROTATE, PLACE

Possible rewards :
    - the direct score --> easy to implement, but problem of delayed reward, making the agent difficult to understand rules
    - the proportion of completed lines --> instant rewards, but trickier to tune so that the agent is actually playing well

Possible environment observations :
    - the whole grid + current and next pieces states

What is Deep in DeepRL :
    - the goal of RL is to find the best trajectory based on an iteratively updated policy function Q(s,a) or value function V(s)
    - because Q or V is very hard to know in real cases (too many states and/or actions), we can approximate it with NNs.



RESOURCES :
    https://medium.com/@jonathan_hui/rl-dqn-deep-q-network-e207751f7ae4

    https://www.youtube.com/watch?v=79pmNdyxEGo
*/

#ifndef TETRIS_AI_H
#define TETRIS_AI_H


struct State
{
    int 
}


class Memory
{

}


class NeuralNetwork
{

}


#endif

