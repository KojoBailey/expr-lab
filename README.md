# Expr Lab
As I am in the process of designing and implementing [Tru lang](https://github.com/KojoBailey/tru-lang), I wanted to test some ideas at a smaller-scale. Hence, this project is a playground for me to implement a small CLI expession evaluator that supports some interesting features.

Doing this not only allows me to test ideas in isolation without having to worry about how getting things "perfect" for Tru, but it also lets me practise implementing a compiler-esque application in C++ at a much smaller scale.

## Stand-Out Features
At the moment, none of these have been implemeneted yet, but the goal is that they will be at least partially.

For starters, lists and tuples use the same set of brackets, `()`:
```lua
(1, 2, 3, 4)
```

Lists can be mapped over without actually using `map`:
```lua
(1, 2, 3, 4) + 7 = (8, 9, 10, 11)
(1, 2, 3, 4) * 3 = (3, 6, 9, 12)
```

Concatenation uses a different operator, as does repetition:
```lua
(1, 2, 3) & (4, 5, 6) = (1, 2, 3, 4, 5, 6)
(1, 2, 3) ** 3 = (1, 2, 3, 1, 2, 3, 1, 2, 3)
```

Types are sets of possible states, and use `{}` brackets:
```lua
1 # {0, 1}
not 5 # {1, 2, 3}
```

Constants can be defined with `let`, and may have type constraints:
```lua
let x = 5
let y # {0, 1} = 0
```

Types can also be defined in this way:
```lua
let Bool = {0, 1}
```

More features will be planned, but I'll start with these.
