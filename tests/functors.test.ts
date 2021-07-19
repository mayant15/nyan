import {Container, Maybe} from '../src/functors'

test('Container functor', () => {
  const container = Container.of(10)
  expect(container.map(x => x * 2)).toEqual(Container.of(20))
})

test('Maybe functor', () => {
  const find = (f, xs: any[]) => Maybe.of(xs.find(f))

  const dataNum = [1, 2, 3, 4]
  const find3 = find(val => val === 3, dataNum) // Maybe(3)
  const find5 = find(val => val === 5, dataNum) // Nothing

  expect(find3).toEqual(Maybe.of(3))
  expect(find3.map(x => x * 2)).toEqual(Maybe.of(6))
  expect(find5).toEqual(Maybe.of(undefined))
  expect(find5.map(x => x * 2)).toEqual(find5)
})
