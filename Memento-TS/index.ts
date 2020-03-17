interface Memento {
    restore(): void
}

interface Originator {
    snapshot(): Memento
}

class ImplTarget implements Originator {
	private state: string
	
	constructor(state: string) {
		this.state = state
	}

    setState(state: string): void {
        this.state = state
    }

    getState(): string {
        return this.state
    }
    
	snapshot(): Memento {
		return new ImplTarget.ImplMemento(this)
    }

    private static ImplMemento = class implements Memento {
        private state: string
        private target: ImplTarget

        constructor(target: ImplTarget) {
            this.state = target.getState()
            this.target = target
        }

        getState(): string {
            return this.state;
        }

        restore(): void {
            this.target.setState(this.state)
        }
    }
}

class Caretaker {
    private target: Originator
    private memento: Array<Memento> = []

    constructor(target: Originator) {
        this.target = target
    }

    rollback(): boolean {
        let tmp = this.memento.pop()
        if (!!tmp) {
            tmp.restore()
            return true
        }
        return false
    }

	snapshot(): void {
		this.memento.push(this.target.snapshot())
    }
}

/**
 * Клиентский код.
 */
let target = new ImplTarget("source")
let cat = new Caretaker(target)

let computedTarget = () => JSON.stringify(target)

console.log(computedTarget())

cat.snapshot()
target.setState('change1')
console.log(computedTarget())

cat.snapshot()
target.setState('change2')
console.log(computedTarget())

cat.rollback()
console.log(computedTarget())

cat.rollback()
console.log(computedTarget())

cat.rollback()
console.log(computedTarget())