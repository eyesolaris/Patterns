
fun main(args: Array<String>) {
   var structure = Bank()
    structure.add(Person("Glazyrin Mikhail","8993559535"))
    structure.add(Company("jetbrains","test", "3255252424"))
    structure.accept(HtmlVisitor())
    structure.accept(XmlVisitor())
}

interface  Visitor {
    fun visitPersonAcc(acc:Person)
    fun visitCompanyAcc(acc:Company)
}

class HtmlVisitor:Visitor {
    override fun visitPersonAcc(acc: Person) {
        var result = "<table><tr><td>Свойство<td><td>Значение</td></tr>"
        result += "<tr><td>FIO<td><td>${acc.fio}</td></tr>"
        result += "<tr><td>Number<td><td>${acc.accNumber}</td></tr></table>"
        println(result)
    }

    override fun visitCompanyAcc(acc: Company) {
        var result = "<table><tr><td>Свойство<td><td>Значение</td></tr>"
        result += "<tr><td>Name<td><td>${acc.name}</td></tr>";
        result += "<tr><td>RegNumber<td><td>${acc.regNumber}r</td></tr>"
        result += "<tr><td>Number<td><td>${acc.number}</td></tr></table>"
        println(result)
    }
}

class XmlVisitor: Visitor {
    override fun visitPersonAcc(acc: Person) {
        val result:String = "<Person><Name>${acc.fio}</Name>"+
                "<Number>${acc.accNumber}</Number><Person>"
        println(result)
    }

    override fun visitCompanyAcc(acc: Company) {
        val result:String = "<Company><Name>${acc.name}</Name>" +
        "<RegNumber>${acc.regNumber}</RegNumber>" +
                "<Number>${acc.number}</Number><Company>";
        println(result)
    }
}

class Bank {
    private var accounts:ArrayList<Account> = ArrayList()

    fun add(acc:Account) {
        accounts.add(acc)
    }

    fun remove(acc:Account) {
        accounts.remove(acc)
    }

    fun accept(visitor: Visitor)
    {
        accounts
            .stream()
            .forEach { it.accept(visitor) }
    }
}

interface Account {
    fun accept(visitor: Visitor)
}

class Person(var fio:String, var accNumber:String):Account {
    override fun accept(visitor: Visitor) {
        visitor.visitPersonAcc(this)
    }
}

class Company(var name:String, var regNumber:String, var number:String): Account {
    override fun accept(visitor: Visitor) {
        visitor.visitCompanyAcc(this)
    }
}
