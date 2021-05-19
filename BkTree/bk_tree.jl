using Pipe: @pipe
using Random

struct BkTreeNode
    word::String
    distance::Int
    children::Array{BkTreeNode}

    BkTreeNode(word, distance) = new(word, distance, BkTreeNode[])
    BkTreeNode(word, distance, children) = new(word, distance, children)
end


struct BkTree
    root::Union{Nothing, BkTreeNode}
    BkTree() = new(nothing)
    BkTree(node) = new(node)
end


function insert(node::BkTreeNode, word::String)
    distance = levenshtein(node.word, word)
    if distance == 0
        throw(ArgumentError("Word already inserted -> $word"))
    end

    for child in node.children
        if child.distance == distance
            baby = insert(child, word)
            children = push!([child_ for child_ in node.children if child_ != child],
                             baby)
            return BkTreeNode(node.word,
                              node.distance,children)
        end
    end

    return BkTreeNode(node.word,
                      node.distance,
                      push!(node.children, BkTreeNode(word, distance)))
end


function insert(tree::BkTree, word::String)
    if tree.root == nothing
        return BkTree(BkTreeNode(word, 0))
    end
    try
        root = insert(tree.root, word)
        return BkTree(root)
    catch e
        if isa(e, ArgumentError)
            return tree
        else
            throw(e)
        end
    end
end


function search(node::BkTreeNode, word::String, threshold::Int)
    distance = levenshtein(node.word, word)
    words = String[]
    if distance <= threshold
        push!(words, node.word)
    end

    for child in node.children
        if child.distance <= distance + threshold && child.distance >= distance - threshold
            words = vcat(words, search(child, word, threshold))
        end
    end
    return words
end


function search(tree::BkTree, word::String, distance::Int=0)
    if tree.root == nothing
        return nothing
    end
    return search(tree.root, word, distance)
end


function levenshtein(one::String, two::String)
    lone, ltwo = length.((one, two))
    lone == 0 && return ltwo
    ltwo == 0 && return lone

    one_, two_ = one[2:end], two[2:end]
    dis = levenshtein(one_, two_)

    if one[1] == two[1]
        return dis
    else
        return 1 + min(dis, levenshtein(one, two_), levenshtein(one_, two))
    end
end


function gviz(node::BkTreeNode, depth)
    subgraph = ""
    for child in node.children
        subgraph *= "\"$(node.word)\" -> \"$(child.word)\";\n"#" [label = \"$(child.distance)\"];\n"
        #subgraph *= "$(node.word) -> $(child.word) [label = \"$(child.distance)\"];\n"
        subgraph *= gviz(child, depth+1)
    end
    return subgraph
end


function gviz(tree::BkTree)
    if tree.root == nothing
        return "graph{}"
    end
    return "digraph BkTree {\n$(gviz(tree.root, 0))\n}"
end


function viz(node::BkTreeNode, depth)
    println(" . " ^ depth * "  $(node.distance) $(node.word)")
    for child in node.children
        viz(child, depth+1)
    end
end


function viz(tree::BkTree)
    if tree.root == nothing
        return nothing
    end
    viz(tree.root, 0)
    return tree
end


function test()
    tree = BkTree()
    open("./words.txt") do file
        words = read(file, String)
        words = split(words, r"\n")
        words = [string(word) for word in words]
        words = shuffle(words)

        for (index, word) in enumerate(words)
            tree = insert(tree, string(word))
        end
    end

    return tree
end

tree = test() #|> viz
@pipe tree |> search(_, "bell", 1) |> println

function name()
    open("tmp.dot", "w+") do dot
        write(dot, gviz(tree))
    end
end
name()
