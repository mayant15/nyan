import {compose} from '../src/base'

test('compose +1 and +2 to equal +3', () => {
  const add1 = (x: number) => x + 1
  const add2 = (y: number) => y + 2
  expect(compose(add2, add1)(0)).toBe(3)
})
