import org.jetbrains.annotations.NotNull;

import java.util.function.Consumer;

public class MyBinaryTree<T extends Comparable<T>> {
    private class Node<T extends Comparable<T>> implements Comparable<Node<T>> {
        Node<T> Left = null;
        Node<T> Right = null;
        T Value;
        Node(T value) {
            Value = value;
        }

        @Override
        public int compareTo(@NotNull Node<T> other) {
            return Value.compareTo(other.Value);
        }

        private void moveTo(Node<T> target) {
            if (target == null) {
                target = this;
                return;
            }
            int compare = compareTo(target);
            if (compare <= 0) target.Left = this;
            else if (compare > 0) target.Right = this;
        }
    }
    Node<T> Root = null;
    public void add(T value) {
        if (Root == null) Root = new Node<>(value);
        else addTo(Root, value);
    }
    public void addTo(Node<T> node, T value) {
        if (value.compareTo(node.Value) <= 0) {
            if (node.Left == null) node.Left = new Node<>(value);
            else addTo(node.Left, value);
        } else {
            if (node.Right == null) node.Right = new Node<>(value);
            else addTo(node.Right, value);
        }
    }

    /**
     * @param subtree Node/branch/subtree to search for result.
     * @param key Key value to search for.
     * @return Node with value equal to key. Null if none found.
     * @see #findWithParent
     */
    private Node<T> findNode(Node<T> subtree, T key) {
        if (subtree == null) return null;
        if (key.compareTo(subtree.Value) == 0) return subtree;
        if (key.compareTo(subtree.Value) <  0) return findNode(subtree.Left,  key);
        else return findNode(subtree.Right, key);
    }

    public boolean Contains(T key) {
        return findNode(Root, key) != null;
    }

    /**
     * @param subtree Node/branch/subtree to search for result.
     * @param parent Returns parent node for found node.
     * @param key Key value to search for.
     * @return Node with value equal to key, parent node via parent parameter. Null if none found.
     * @see #findNode
     */
    private Node<T> findWithParent(Node<T> subtree, Node<T> parent, T key) {
        if (subtree == null) {
            parent = null;
            return null;
        }
        if (subtree == Root) parent = null;
        if (key.compareTo(subtree.Value) == 0) return subtree;
        parent = subtree;
        if (key.compareTo(subtree.Value) <  0) return findWithParent(subtree.Left, parent, key);
        else                                   return findWithParent(subtree.Right, parent, key);
    }

    /**
     * @param key
     */
    public void Remove(T key) {
        Node<T> parent = null;
        Node<T> target = findWithParent(Root, parent, key);
        if (target == null) return;
        // No right child nodes
        if (target.Right == null) {
            if (parent == null) Root = target.Left;
            else {
                target.Left.moveTo(parent);
            }
        }
        // Right child node without left child nodes
        if (target.Right != null && target.Right.Left == null) {
            target.Right.Left = target.Left;
            if (parent == null) Root = target.Right;
            else {
                target.Right.moveTo(parent);
            }
        }
        // Right child node with left child nodes
        if (target.Right != null && target.Right.Left != null) {
            Node<T> leftestNode = target.Right.Left;
            Node<T> leftestNodeParent = target.Right;
            while (leftestNode.Left != null) {
                leftestNodeParent = leftestNode;
                leftestNode = leftestNode.Left;
            }
            leftestNodeParent.Left = leftestNode.Right;

            leftestNode.Left = target.Left;
            leftestNode.Right = target.Right;

            if (parent == null) Root = leftestNode;
            else {
                leftestNode.moveTo(parent);
            }
        }
    }
    public void travelPostOrder(Consumer<T> functionLambda) {
        travelPostOrder(functionLambda, Root);
    }

    private void travelPostOrder(Consumer<T> functionLambda, Node<T> node) {
        if (node != null) {
            travelPostOrder(functionLambda, node.Left);
            travelPostOrder(functionLambda, node.Right);
            functionLambda.accept(node.Value);
        }
    }

    public void travelPreOrder(Consumer<T> functionLambda) {
        travelPreOrder(functionLambda, Root);
    }

    private void travelPreOrder(Consumer<T> functionLambda, Node<T> node) {
        if (node != null) {
            functionLambda.accept(node.Value);
            travelPreOrder(functionLambda, node.Left);
            travelPreOrder(functionLambda, node.Right);
        }
    }

    public void travelInOrder(Consumer<T> functionLambda) {
        travelInOrder(functionLambda, Root);
    }

    private void travelInOrder(Consumer<T> functionLambda, Node<T> node) {
        if (node != null) {
            travelInOrder(functionLambda, node.Left);
            functionLambda.accept(node.Value);
            travelInOrder(functionLambda, node.Right);
        }
    }
}