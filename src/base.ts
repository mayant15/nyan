export const compose =
  (f: any, g: any): any =>
  (x: any): any =>
    f(g(x))

export const sum = (x: number, y: number): any => x + y
