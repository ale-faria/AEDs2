
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

class Pokemon{
    private int id;
    private int generation;
    private String name;
    private String description;
    private List<String> types = new ArrayList<>();
    private List<String> abilities = new ArrayList<>();
    private double weight;
    private double height;
    private int captureRate;
    private boolean isLegendary;
    private Date captureDate;

    Pokemon(){}

    Pokemon(int id, String name, String description, List<String> types, List<String> abilities, double weight, double height, int captureRate, boolean isLegendary, Date captureDate ){
        this.id = id;
        this.name = name;
        this.description = description;
        this.types = types;
        this.abilities = abilities;
        this.weight = weight;
        this.height = height;
        this.captureRate = captureRate;
        this.isLegendary = isLegendary;
        this.captureDate = captureDate;

    }

    int getId(){
        return id;
    }

    int getGeneration(){
        return generation;
    }

    String getName(){
        return name;
    }

    String getDescription(){
        return description;
    }

    List<String> getTypes(){
        return types;
    }

    List<String> getAbilities(){
        return abilities;
    }

    public double getWeight(){
        return weight;
    }

    public double getHeight(){
        return height;
    }

    public int getCaptureRate() {
        return captureRate;
    }

    public boolean isIsLegendary() {
        return isLegendary;
    }

    public Date getCaptureDate() {
        return captureDate;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setGeneration(int generation) {
        this.generation = generation;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public void setTypes(List<String> types) {
        this.types = types;
    }

    public void setAbilities(List<String> abilities) {
        this.abilities = abilities;
    }

    public void setWeight(double weight) {
        this.weight = weight;
    }

    public void setHeight(double height) {
        this.height = height;
    }

    public void setCaptureRate(int captureRate) {
        this.captureRate = captureRate;
    }

    public void setIsLegendary(boolean isLegendary) {
        this.isLegendary = isLegendary;
    }

    public void setCaptureDate(Date captureDate) {
        this.captureDate = captureDate;
    }

}

public class TP02{
    public static void main(String[] args){
        
    }
}