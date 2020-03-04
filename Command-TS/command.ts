interface Command{
  do(): void;
}

class Real1 implements Command {
  do(): void {
    console.log(`Class: ${this.constructor.name}`);
  }
}

class Real2 implements Command {
  do(): void {
    console.log(`Class: ${this.constructor.name}`);
  }
}

class Invoker {
  listOfCommand: Array<Command> = new Array<Command>();
  setCommand(command: Command): void {
    this.listOfCommand.push(command);
  }

  doAll(): void {
      this.listOfCommand.forEach(comma => comma.do());
      this.listOfCommand = new Array<Command>();
  }
}

const invoker = new Invoker();
invoker.setCommand(new Real1);
invoker.setCommand(new Real2);
invoker.doAll();
