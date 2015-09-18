import org.junit.Test;

import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

public class MyBinaryTreeTests {
    @Test
    public void testConstructor() {
        MyBinaryTree<Integer> testTree = new MyBinaryTree<>();
        assertNotNull(testTree);
    }
    @Test
    public void testAdder() {
        MyBinaryTree<Student> testTree = new MyBinaryTree<>();
        testTree.add(new Student("Karpova", 4374));
        testTree.add(new Student("Sereda", 4374));
        testTree.add(new Student("Kuptsova", 4374));
    }
    @Test
    public void testContains() {
        MyBinaryTree<Student> testTree = new MyBinaryTree<>();
        testTree.add(new Student("Karpova", 4374));
        testTree.add(new Student("Sereda", 4374));
        testTree.add(new Student("Kuptsova", 4374));
        assertTrue(testTree.Contains(new Student("Sereda", 4374)));
    }
    @Test
    public void testRemove() {
        MyBinaryTree<Student> testTree = new MyBinaryTree<>();
        testTree.add(new Student("Karpova", 4374));
        testTree.add(new Student("Sereda", 4374));
        testTree.add(new Student("Kuptsova", 4374));
        testTree.add(new Student("Kozachek", 4374));
        testTree.Remove(new Student("Karpova", 4374));
    }
    @Test
    public void testTravel() {
        MyBinaryTree<Student> testTree = new MyBinaryTree<>();
        testTree.add(new Student("Karpova", 4374));
        testTree.add(new Student("Sereda", 4374));
        testTree.add(new Student("Kuptsova", 4374));
        testTree.add(new Student("Kozachek", 4374));
        System.out.println("Postorder");
        testTree.travelPostOrder(student -> System.out.println(student.toString()));
        System.out.println("Preorder");
        testTree.travelPreOrder(student -> System.out.println(student.toString()));
        System.out.println("Inorder");
        testTree.travelInOrder(student -> System.out.println(student.toString()));
    }
}
