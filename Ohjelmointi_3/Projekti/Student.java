/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Other/File.java to edit this template
 */
package fi.tuni.prog3.sisu2;

import java.util.TreeSet;

/**
 *
 * @author Jenna
 */
public class Student {
    public String studentName;
    public String studentNumber;
    public TreeSet<String> courses = new TreeSet<>();
    /**
     * Alustaa student oliolle nimen ja opiskelijanumeron
     * @param name Opiskelijan nimi
     * @param number Opiskelijanumero
     */
    public Student(String name, String number) {
        studentName = name;
        studentNumber = number;
    }
    /**
     * Palauttaa opiskelijan nimen
     * @return Opiskelijan nimi
     */
    public String getName() {
        return studentName;
    }
    /**
     * Palauttaa opiskelijanumeron
     * @return Opiskelijanumero
     */
    public String getNumber() {
        return studentNumber;
    }
    /**
     * Palauttaa setin, joka sisaltaa kaikki opiskelijan kurssit.
     * @return Kaikki kurssit
     */
    public TreeSet<String> getCourses() {
        return courses;
    }
    /**
     * Lisaa kurssin opiskelijan kurssilistaan
     * @param course Lisattavan kurssin nimi
     */
    public void addCourses(String course) {
        courses.add(course);
    }
    /**
     * Poistaa kurssin opiskelijan kurssilistasta
     * @param course Poistettavan kurssin nimi
     */
    public void removeCourses(String course) {
        courses.remove(course);
    }
    
    
}
