import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class AlgBool {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextLine()) {
            String input = scanner.nextLine();
            System.out.println(evaluateExpression(input) ? "SIM" : "NAO");
        }
        scanner.close();
    }

    public static boolean evaluateExpression(String input) {
        String[] parts = input.split(" ");
        int n = Integer.parseInt(parts[0]);
        boolean[] values = new boolean[n];
        for (int i = 0; i < n; i++) {
            values[i] = parts[i + 1].equals("1");
        }
        String expression = input.substring(input.indexOf(parts[n + 1]));

        Map<String, Boolean> variables = new HashMap<>();
        for (int i = 0; i < n; i++) {
            variables.put(String.valueOf((char) ('A' + i)), values[i]);
        }

        return evaluate(parseExpression(expression), variables);
    }

    private static Node parseExpression(String expression) {
        expression = expression.replaceAll(" ", "");
        return parseOr(expression);
    }

    private static Node parseOr(String expression) {
        List<Node> children = new ArrayList<>();
        int depth = 0;
        int start = 0;
        for (int i = 0; i < expression.length(); i++) {
            char c = expression.charAt(i);
            if (c == '(') depth++;
            if (c == ')') depth--;
            if (depth == 0 && expression.startsWith("or", i)) {
                children.add(parseAnd(expression.substring(start, i)));
                start = i + 2;
            }
        }
        children.add(parseAnd(expression.substring(start)));
        return new Node("or", children);
    }

    private static Node parseAnd(String expression) {
        List<Node> children = new ArrayList<>();
        int depth = 0;
        int start = 0;
        for (int i = 0; i < expression.length(); i++) {
            char c = expression.charAt(i);
            if (c == '(') depth++;
            if (c == ')') depth--;
            if (depth == 0 && expression.startsWith("and", i)) {
                children.add(parseNot(expression.substring(start, i)));
                start = i + 3;
            }
        }
        children.add(parseNot(expression.substring(start)));
        return new Node("and", children);
    }

    private static Node parseNot(String expression) {
        if (expression.startsWith("not(") && expression.endsWith(")")) {
            return new Node("not", Collections.singletonList(parseOr(expression.substring(4, expression.length() - 1))));
        }
        return parseVariable(expression);
    }

    private static Node parseVariable(String expression) {
        if (expression.startsWith("(") && expression.endsWith(")")) {
            return parseOr(expression.substring(1, expression.length() - 1));
        }
        return new Node(expression);
    }

    private static boolean evaluate(Node node, Map<String, Boolean> variables) {
        switch (node.value) {
            case "or":
                for (Node child : node.children) {
                    if (evaluate(child, variables)) return true;
                }
                return false;
            case "and":
                for (Node child : node.children) {
                    if (!evaluate(child, variables)) return false;
                }
                return true;
            case "not":
                return !evaluate(node.children.get(0), variables);
            default:
                return variables.get(node.value);
        }
    }

    static class Node {
        String value;
        List<Node> children;

        Node(String value) {
            this.value = value;
            this.children = new ArrayList<>();
        }

        Node(String value, List<Node> children) {
            this.value = value;
            this.children = children;
        }
    }
}
