export const compose = (f, g) => x => f(g(x))

export const curry = f => x => y => f(x, y)
