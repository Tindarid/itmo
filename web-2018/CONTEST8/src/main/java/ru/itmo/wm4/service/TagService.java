package ru.itmo.wm4.service;

import org.springframework.stereotype.Service;
import ru.itmo.wm4.domain.Tag;
import ru.itmo.wm4.repository.TagRepository;

import java.util.*;

@Service
public class TagService {
    private final TagRepository tagRepository;

    public TagService(TagRepository tagRepository) {
        this.tagRepository = tagRepository;
    }

    public Set<Tag> save(String[] tags) {
        List<Tag> all = tagRepository.findAll();
        Map<String, Tag> map = new HashMap<>();
        Set<Tag> ans = new HashSet<>();
        for (Tag tag : all) {
            map.put(tag.getName(), tag);
        }
        for (String tag : tags) {
            if (!map.containsKey(tag)) {
                Tag newTag = new Tag();
                newTag.setName(tag);
                tagRepository.save(newTag);
                ans.add(newTag);
            } else {
                ans.add(map.get(tag));
            }
        }
        return ans;
    }
}
