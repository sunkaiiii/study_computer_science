package com.example.jetpacktest

class Table {
    private val children = ArrayList<Tr>()
    fun tr(block: Tr.() -> Unit) {
        val tr = Tr()
        tr.block()
        children.add(tr)
    }
    fun html(): String {
        val builder = StringBuilder()
        builder.append("<table>")
        for (childTag in children) {
            builder.append(childTag.html())
        }
        builder.append("\n</table>")
        return  builder.toString()
    }
}

fun table(block: Table.() -> Unit): String {
    val table = Table()
    table.block()
    return table.html()
}