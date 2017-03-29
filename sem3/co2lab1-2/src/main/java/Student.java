
public class Student implements Comparable<Student> {
    private String lastName;
    private int groupNumber;

    public Student(String lastName, Integer groupNumber) {
        setLastName(lastName);
        setGroupNumber(groupNumber);
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public Integer getGroupNumber() {
        return groupNumber;
    }

    public void setGroupNumber(Integer groupNumber) {
        this.groupNumber = groupNumber;
    }

    @Override
    public int compareTo(Student other) {
        return lastName.compareTo(other.getLastName());
    }

    @Override
    public String toString() {
        return "Student " + getLastName() + " from group " + getGroupNumber();
    }
}
