export class Container {
  constructor(private readonly value) {}

  static of(value) {
    return new Container(value)
  }

  map(f) {
    return Container.of(f(this.value))
  }
}

export class Maybe {
  constructor(private readonly value) {}

  static of(value) {
    return new Maybe(value)
  }

  private isNone() {
    return this.value === null || this.value === undefined
  }

  map(f) {
    return this.isNone() ? this : Maybe.of(f(this.value))
  }
}
