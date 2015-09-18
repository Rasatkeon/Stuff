import org.junit.Test;
import static org.junit.Assert.*;

public class MyListTests {
    @Test
    public void testConstructor() {
        MyList<Integer> List = new MyList<>();
        assertNotNull(List);
    }
    @Test
    public void testAppender() {
        MyList<Integer> List = new MyList<>();
        List.append(9);
        assertEquals(List.getSize(), 1);
    }
    @Test
    public void testFirstGetter() {
        MyList<Integer> List = new MyList<>();
        List.append(9);
        assertEquals(List.getFirst(), new Integer(9));
    }
    @Test
    public void testRemover() {
        MyList<Integer> List = new MyList<>();
        List.append(9);
        List.removeFirst(9);
        assertNull(List.getFirst());
        List.append(9);
        List.append(42);
        List.removeFirst(9);
        assertEquals(List.getSize(), 1);
        assertEquals(List.getFirst(), new Integer(42));
        assertEquals(List.removeFirst(23), false);
    }
    @Test
    public void testGetFirst() {
        MyList<Integer> List = new MyList<>();
        for ( int i = 0; i <= 10; i++ ) {
            List.append(i);
        }
        assertEquals(List.getFirst(9).get(), new Integer(9));
        assertEquals(List.getSize(), 10);
    }
    @Test
    public void testAdder() {
        MyList<Integer> List = new MyList<>();
        for ( int i = 0; i <= 10; i++ ) {
            List.append(i);
        }
        List.addAfter(9, 42);
        List.removeFirst(10);
        assertEquals(List.getLast(), new Integer(42));
    }
}
