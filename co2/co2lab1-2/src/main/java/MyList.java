import java.util.Optional;

/**
 * Custom realisation of abstract data structure `List`
 * @param <T> Data type contained in MyList.
 */
public class MyList<T> {
    /**
     * Inner class to represent list node.
     * @param <T> Data type for value contained in Node.
     * @see MyList
     */
    final private class Node<T> {
        private T Data = null;
        private Node<T> Next = null;
        private Node<T> Prev = null;

        public Node(T data) {
            this.Data = data;
        }

        public T getData() {
            return Data;
        }
    }

    /**
     * List size.
     */
    private int Size = 0;

    /**
     * Head of the list.
     */
    private Node<T> First = null;
    /**
     * Reverse head of the list.
     */
    private Node<T> Last = null;

    /**
     * @return List size
     */
    public int getSize() {
        return Size;
    }

    /**
     * Adds a node with a value to the end of the list.
     * @param value Value for a new node.
     * @see #addAfter(Object, Object)
     */
    public void append(T value) {
        Size++;
        if (First == null) First = Last = new Node<>(value);
        else {
            Last.Next = new Node<>(value);
            Last.Next.Prev = Last;
            Last = Last.Next;
        }
    }

    /**
     * Inserts node with a value after a certain node.
     * @param key Value of node to insert after.
     * @param value Value of node to insert.
     * @return `true` if succeeded `false` if not.
     * @see #append(Object)
     */
    public boolean addAfter(T key, T value) {
        Node<T> keyNode = searchFirstNode(key).get();
        if (keyNode == null) return false;
        else {
            Node<T> nextNode = keyNode.Next;
            keyNode.Next = new Node<>(value);
            keyNode.Next.Next = nextNode;
            nextNode.Prev = keyNode.Next;
            keyNode.Next.Prev = keyNode;
            return true;
        }
    }

    /**
    @return `null` if list is empty. Otherwise first node value.
     */
    public T getFirst() {
        if (First == null) {
            return null;
        } else {
            return First.getData();
        }
    }
    /**
     @return `null` if list is empty. Otherwise last node value.
     */
    public T getLast() {
        if (Last == null) {
            return null;
        } else {
            return Last.getData();
        }
    }

    /**
     * Removes certain node.
     * @param node Node to remove.
     * @see #removeFirst(Object)
     */
    private void removeThis(Node<T> node) {
        if (node == null) return;
        Size--;
        if (node.Prev != null) node.Prev.Next = node.Next;
        else First = node.Next;
        if (node.Next != null) node.Next.Prev = node.Prev;
        else Last = node.Prev;
        node.Data = null;
    }

    /**
     * Searches for a first node with a certain value.
     * @param key Value to search for.
     * @return <code>Optional.empty</code> if none found. Otherwise <code>Optional.of({@link MyList.Node})</code>.
     */
    private Optional<Node<T>> searchFirstNode(T key) {
        // No elements in list
        if (First == null) return Optional.empty();
        else {
            Node<T> currNode = First;
            while (currNode != null) {
                if (currNode.Data.equals(key)) {
                    // Element equal to key was removed
                    return Optional.of(currNode);
                } else {
                    currNode = currNode.Next;
                }
            }
            // No element equals to key
            return Optional.empty();
        }
    }

    /**
     * Removes first node with a certain value.
     * @param key Value to look for.
     * @return `true` if succeeded `false` if not.
     * @see #removeThis(Node)
     */
    public boolean removeFirst(T key) {
        // No elements in list
        if (First == null) return false;
        else {
            Node<T> currNode = First;
            while (currNode != null) {
                if (currNode.Data.equals(key)) {
                    removeThis(currNode);
                    // Element equal to key was removed
                    return true;
                } else {
                    currNode = currNode.Next;
                }
            }
        }
        // No element equals to key
        return false;
    }


    /**
     * Returns data contained in a certain Node. Removes this node from the list.
     * @param key Value of node to search for.
     * @return <code>Optional.empty()</code> if not found or empty list. Otherwise <code>Optional.of({@link T})</code>
     */
    public Optional<T> getFirst(T key) {
        if (First == null) return Optional.empty();
        else {
            Node<T> currNode = First;
            while (currNode != null) {
                if (currNode.Data.equals(key)) {
                    // Element equal to key found
                    Optional<T> result = Optional.of(currNode.getData());
                    removeThis(currNode);
                    return result;
                } else {
                    currNode = currNode.Next;
                }
            }
            return Optional.empty();
        }
    }
}
