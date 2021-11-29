all: p1-s p1-c p2-s p2-c p3-s p3-c

p1-s: p1-s.c
	gcc $< -o $@

p1-c: p1-c.c
	gcc $< -o $@

p2-s: p2-s.c
	gcc $< -o $@

p2-c: p2-c.c
	gcc $< -o $@

p3-c: p3-c.c
	gcc $< -o $@

p3-s: p3-s.c
	gcc $< -o $@

clean:
	rm p1-s p1-c p2-s p2-c p3-s p3-c

re: fclean all
